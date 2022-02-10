#include "http.h"
#include "json_proxy.h"
#include "json_proxy_config_items.h"
#include "json_proxy_config_updates.h"
#include "json_proxy_config_validators.h"
#include "json_proxy_log.h"
#include "json_proxy_operations.h"
#include "json_proxy_proto.h"
#include "json_proxy_toggle_config_validator.h"
#include "base_handler.h"
#include "walle.h"

#include <ydb/core/base/appdata.h>
#include <ydb/core/mon/mon.h>

#include <library/cpp/actors/core/actor_bootstrapped.h>
#include <library/cpp/actors/core/hfunc.h>
#include <library/cpp/actors/core/mon.h>
#include <library/cpp/mime/types/mime.h>
#include <library/cpp/resource/resource.h>

namespace NKikimr {
namespace NCms {

template <typename HandlerActorType>
class TApiMethodHandler : public TApiMethodHandlerBase {
public:
    IActor *CreateHandlerActor(NMon::TEvHttpInfo::TPtr &event) override
    {
        return new HandlerActorType(event);
    }
};

class TCmsHttp : public TActorBootstrapped<TCmsHttp> {
public:
    static constexpr NKikimrServices::TActivity::EType ActorActivityType() 
    {
        return NKikimrServices::TActivity::CMS_SERVICE_PROXY; 
    }

    void Bootstrap(const TActorContext &ctx)
    {
        Become(&TThis::StateWork);
        NActors::TMon *mon = AppData(ctx)->Mon;
        if (mon) {
            mon->RegisterActorPage(nullptr, "cms", "Cluster Management System", false, ctx.ExecutorThread.ActorSystem, ctx.SelfID);

            ApiHandlers["/api/clusterstaterequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvClusterStateRequest,
                                                                                          TEvCms::TEvClusterStateResponse>>;
            ApiHandlers["/api/permissionrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvPermissionRequest,
                                                                                        TEvCms::TEvPermissionResponse>>;
            ApiHandlers["/api/managerequestrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvManageRequestRequest,
                                                                                           TEvCms::TEvManageRequestResponse>>;
            ApiHandlers["/api/checkrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvCheckRequest,
                                                                                   TEvCms::TEvPermissionResponse>>;
            ApiHandlers["/api/managepermissionrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvManagePermissionRequest,
                                                                                              TEvCms::TEvManagePermissionResponse>>;
            ApiHandlers["/api/conditionalpermissionrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvConditionalPermissionRequest,
                                                                                                   TEvCms::TEvPermissionResponse>>;
            ApiHandlers["/api/notification"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvNotification,
                                                                                   TEvCms::TEvNotificationResponse>>;
            ApiHandlers["/api/managenotificationrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvManageNotificationRequest,
                                                                                                TEvCms::TEvManageNotificationResponse>>;
            ApiHandlers["/api/managenotificationrequest"] = new TApiMethodHandler<TJsonProxyCms<TEvCms::TEvManageNotificationRequest,
                                                                                                TEvCms::TEvManageNotificationResponse>>;

            ApiHandlers["/api/console/configure"] = new TApiMethodHandler<TJsonProxyConsole<NConsole::TEvConsole::TEvConfigureRequest,
                                                                                            NConsole::TEvConsole::TEvConfigureResponse>>;
            ApiHandlers["/api/json/log"] = new TApiMethodHandler<TJsonProxyLog>;
            ApiHandlers["/api/json/configitems"] = new TApiMethodHandler<TJsonProxyConfigItems>;
            ApiHandlers["/api/json/configvalidators"] = new TApiMethodHandler<TJsonProxyConfigValidators>;
            ApiHandlers["/api/json/toggleconfigvalidator"] = new TApiMethodHandler<TJsonProxyToggleConfigValidator>;
            ApiHandlers["/api/json/configupdates"] = new TApiMethodHandler<TJsonProxyConfigUpdates>;
            ApiHandlers["/api/json/proto"] = new TApiMethodHandler<TJsonProxyProto>;

            ApiHandlers["/api/datashard/json/getinfo"]
                = new TApiMethodHandler<TJsonProxyDataShard<TEvDataShard::TEvGetInfoRequest,
                                                            TEvDataShard::TEvGetInfoResponse>>;
            ApiHandlers["/api/datashard/json/listoperations"]
                = new TApiMethodHandler<TJsonProxyDataShard<TEvDataShard::TEvListOperationsRequest,
                                                            TEvDataShard::TEvListOperationsResponse>>;
            ApiHandlers["/api/datashard/json/getoperation"]
                = new TApiMethodHandler<TJsonProxyDataShardGetOperation>;
            ApiHandlers["/api/datashard/json/getreadtablesinkstate"]
                = new TApiMethodHandler<TJsonProxyDataShardGetReadTableSinkState>;
            ApiHandlers["/api/datashard/json/getreadtablescanstate"]
                = new TApiMethodHandler<TJsonProxyDataShardGetReadTableScanState>;
            ApiHandlers["/api/datashard/json/getreadtablestreamstate"]
                = new TApiMethodHandler<TJsonProxyDataShardGetReadTableStreamState>;
            ApiHandlers["/api/datashard/json/getslowopprofiles"]
                = new TApiMethodHandler<TJsonProxyDataShardGetSlowOpProfiles>;
            ApiHandlers["/api/datashard/json/getrsinfo"]
                = new TApiMethodHandler<TJsonProxyDataShardGetRSInfo>;
            ApiHandlers["/api/datashard/json/getdatahist"]
                = new TApiMethodHandler<TJsonProxyDataShardGetDataHistogram>;

            ApiHandlers[WALLE_API_URL_PREFIX] = new TWalleApiHandler;
        }
    }

private:
    STFUNC(StateWork)
    {
        switch (ev->GetTypeRewrite()) {
            HFunc(NMon::TEvHttpInfo, Handle);
        }
    }

    void ReplyWithFile(NMon::TEvHttpInfo::TPtr &ev,
                       const TActorContext &ctx,
                       const TString& name)
    {
        TString filename = TString("cms/ui") + name;
        if (filename.EndsWith('/'))
            filename += "index.html";
        else if (name == "")
            filename += "/index.html";

        TString blob;
        TString type;
        if (NResource::FindExact(filename, &blob))
            type = mimetypeByExt(filename.c_str());

        if (blob.empty()) {
            ctx.Send(ev->Sender, new NMon::TEvHttpInfoRes(TString(NMonitoring::HTTPNOTFOUND), 0,
                                                          NMon::IEvHttpInfoRes::EContentType::Custom));
            return;
        }

        if (filename == "cms/ui/index.html") { 
            type = "text/html";
        } 
 
        TStringStream response; 
        response << "HTTP/1.1 200 Ok\r\n"; 
        response << "Content-Type: " << type << "\r\n"; 
        response << "Content-Length: " << blob.size() << "\r\n"; 
        response << "\r\n"; 
        response.Write(blob.data(), blob.size()); 
        ctx.Send(ev->Sender, new NMon::TEvHttpInfoRes(response.Str(), 0, NMon::IEvHttpInfoRes::EContentType::Custom)); 
    }

    static TString DumpRequest(const NMonitoring::IMonHttpRequest& request) {
        TStringBuilder result;
        result << "{";

        result << " Method: " << request.GetMethod()
               << " Uri: " << request.GetUri();

        result << " Headers {";
        for (const auto& header : request.GetHeaders()) {
            if (stricmp(header.Name().data(), "Authorization") == 0) {
                continue;
            }

            result << " " << header.ToString();
        }
        result << " }";

        result << " Body: " << request.GetPostContent().Head(1000);

        result << " }";
        return result;
    }

    void Handle(NMon::TEvHttpInfo::TPtr &ev, const TActorContext &ctx)
    {
        Y_UNUSED(ctx);

        NMon::TEvHttpInfo *msg = ev->Get();

        LOG_DEBUG_S(ctx, NKikimrServices::CMS, "HTTP request"
            << ": dump# " << DumpRequest(msg->Request));

        // Check for API call.
        if (msg->Request.GetPathInfo().StartsWith("/api/")) {
            // Check for Wall-E call.
            if (msg->Request.GetPathInfo().StartsWith(WALLE_API_URL_PREFIX)) {
                ctx.ExecutorThread.RegisterActor(ApiHandlers.find(WALLE_API_URL_PREFIX)->second->CreateHandlerActor(ev));
                return;
            }

            auto it = ApiHandlers.find(msg->Request.GetPathInfo());
            if (it != ApiHandlers.end()) {
                ctx.ExecutorThread.RegisterActor(it->second->CreateHandlerActor(ev));
                return;
            }

            // Wrong API method called.
            ctx.Send(ev->Sender, new NMon::TEvHttpInfoRes(TString(NMonitoring::HTTPNOTFOUND) + HELP_LINK, 0,
                                                          NMon::IEvHttpInfoRes::EContentType::Custom));
            return;
        }

        ReplyWithFile(ev, ctx, TString{msg->Request.GetPathInfo()});
    }

    THashMap<TString, TAutoPtr<TApiMethodHandlerBase>> ApiHandlers;

    const TStringBuf HELP_LINK = "Check /api/help for usage details";
};

IActor *CreateCmsHttp() {
    return new TCmsHttp();
}

} // NCms
} // NKikimr
