#pragma once

#include "audit_log.h"

#include <ydb/core/base/defs.h>

#include <library/cpp/actors/core/actor.h>
#include <library/cpp/actors/core/actor_bootstrapped.h>
#include <library/cpp/actors/core/hfunc.h>
#include <ydb/core/mon/mon.h>
#include <library/cpp/actors/core/mon.h>
#include <ydb/core/base/appdata.h>
#include <ydb/core/base/tablet_pipe.h>
#include <ydb/core/cms/cms.h>
#include <ydb/core/cms/console/console.h>
#include <ydb/core/tx/datashard/datashard.h>

#include <library/cpp/protobuf/json/json2proto.h>
#include <library/cpp/protobuf/json/proto2json.h>

#include <iostream>

namespace NKikimr {
namespace NCms {

template <typename TRequestEvent, typename TResponseEvent>
class TJsonProxyBase : public TActorBootstrapped<TJsonProxyBase<TRequestEvent, TResponseEvent>> {
private:
    using TBase = TActorBootstrapped<TJsonProxyBase<TRequestEvent, TResponseEvent>>;

protected:
    using TRequest = TRequestEvent;
    using TResponse = TResponseEvent;

public:
    static constexpr NKikimrServices::TActivity::EType ActorActivityType() 
    {
        return NKikimrServices::TActivity::CMS_SERVICE_PROXY; 
    }

    TJsonProxyBase(NMon::TEvHttpInfo::TPtr &event)
        : RequestEvent(event)
    {
    }

    void Bootstrap(const TActorContext &ctx)
    {
        LOG_DEBUG_S(ctx, NKikimrServices::CMS,
                    "TJsonProxyBase::Bootstrap url=" << RequestEvent->Get()->Request.GetPathInfo());

        auto dinfo = AppData(ctx)->DomainsInfo;
        if (dinfo->Domains.size() != 1) {
            ReplyWithErrorAndDie(TString("HTTP/1.1 501 Not Implemented\r\n\r\nMultiple domains are not supported."), ctx);
            return;
        }

        TAutoPtr<TRequestEvent> request = PrepareRequest(ctx);
        if (!request) {
            LOG_ERROR_S(ctx, NKikimrServices::CMS,
                        "TJsonProxyBase no request to send was built");
            return;
        }

        ui64 tid = GetTabletId(ctx);
        if (!tid) {
            ReplyWithErrorAndDie(TString(NMonitoring::HTTPNOTFOUND) + " unknown tablet ID", ctx);
            return;
        }

        LOG_TRACE_S(ctx, NKikimrServices::CMS,
                    "TJsonProxyBase send request to " << GetTabletName() << " tablet " << tid);

        NTabletPipe::TClientConfig pipeConfig;
        pipeConfig.RetryPolicy = {.RetryLimitCount = 10};
        Pipe = ctx.RegisterWithSameMailbox(NTabletPipe::CreateClient(ctx.SelfID, tid, pipeConfig));
        NTabletPipe::SendData(ctx, Pipe, request.Release());

        TBase::Become(&TBase::TThis::StateWork, ctx, TDuration::Seconds(120), new TEvents::TEvWakeup());
    }

    virtual TAutoPtr<TRequestEvent> PrepareRequest(const TActorContext &ctx) = 0;
    virtual ui64 GetTabletId(const TActorContext &ctx) const = 0;
    virtual TString GetTabletName() const = 0;

protected:
    STFUNC(StateWork)
    {
        switch (ev->GetTypeRewrite()) {
            HFunc(TResponseEvent, Handle);
            CFunc(TEvents::TSystem::Wakeup, Timeout);
            CFunc(TEvTabletPipe::TEvClientDestroyed::EventType, Disconnect);
            HFunc(TEvTabletPipe::TEvClientConnected, Handle);
        default:
            LOG_DEBUG(ctx, NKikimrServices::CMS, "HTTP::StateWork ignored event type: %" PRIx32 " event: %s",
                      ev->GetTypeRewrite(), ev->HasEvent() ? ev->GetBase()->ToString().data() : "serialized?");
        }
    }

    void ReplyWithErrorAndDie(const TString &err, const TActorContext &ctx)
    {
        ReplyAndDieImpl(err, ctx);
    }

    void ReplyAndDie(const typename TResponseEvent::ProtoRecordType &resp, const TActorContext &ctx)
    {
        auto config = NProtobufJson::TProto2JsonConfig()
            .SetFormatOutput(false)
            .SetEnumMode(NProtobufJson::TProto2JsonConfig::EnumName)
            .SetStringifyLongNumbers(NProtobufJson::TProto2JsonConfig::StringifyLongNumbersForDouble);

        auto json = NProtobufJson::Proto2Json(resp, config);
        ReplyAndDie(json, ctx);
    }

    void ReplyAndDie(const TString &json, const TActorContext &ctx)
    {
        ReplyAndDieImpl(TString(NMonitoring::HTTPOKJSON) + json, ctx);
    }

    void ReplyAndDieImpl(const TString &data, const TActorContext &ctx)
    {
        AuditLog("JsonProxy", RequestEvent, data, ctx);
        ctx.Send(RequestEvent->Sender, new NMon::TEvHttpInfoRes(data, 0, NMon::IEvHttpInfoRes::EContentType::Custom));
        TBase::Die(ctx);
    }

    void Die(const TActorContext& ctx) override
    {
        NTabletPipe::CloseClient(ctx, Pipe);
        TBase::Die(ctx);
    }

    void Handle(typename TResponseEvent::TPtr &ev, const TActorContext &ctx)
    {
        ReplyAndDie(ev->Get()->Record, ctx);
    }

    void SetTempError(NKikimrCms::TStatus &status,
                      const TString &error)
    {
        status.SetCode(NKikimrCms::TStatus::ERROR_TEMP);
        status.SetReason(error);
    }

    void SetTempError(NKikimrConsole::TStatus &status,
                      const TString &error)
    {
        status.SetCode(Ydb::StatusIds::UNAVAILABLE);
        status.SetReason(error);
    }

    void SetTempError(NKikimrTxDataShard::TStatus &status,
                      const TString &error)
    {
        status.SetCode(Ydb::StatusIds::UNAVAILABLE);
        auto *issue = status.AddIssues();
        issue->set_severity(NYql::TSeverityIds::S_ERROR);
        issue->set_message(error);
    }

    void Timeout(const TActorContext& ctx)
    {
        typename TResponseEvent::ProtoRecordType rec;
        SetTempError(*rec.MutableStatus(), "Request timeout.");
        ReplyAndDie(rec, ctx);
    }

    void Disconnect(const TActorContext& ctx)
    {
        typename TResponseEvent::ProtoRecordType rec;
        SetTempError(*rec.MutableStatus(), GetTabletName() + " disconnected.");
        ReplyAndDie(rec, ctx);
    }

    void Handle(TEvTabletPipe::TEvClientConnected::TPtr &ev, const TActorContext &ctx) noexcept
    {
        if (ev->Get()->Status != NKikimrProto::OK) {
            typename TResponseEvent::ProtoRecordType rec;
            SetTempError(*rec.MutableStatus(), GetTabletName() + " is unavailable.");
            ReplyAndDie(rec, ctx);
        }
    }

    NMon::TEvHttpInfo::TPtr RequestEvent;
    TActorId Pipe;
};

template <typename TRequestEvent, typename TResponseEvent>
class TJsonProxy : public TJsonProxyBase<TRequestEvent, TResponseEvent> {
private:
    using TBase = TJsonProxyBase<TRequestEvent, TResponseEvent>;

public:
    TJsonProxy(NMon::TEvHttpInfo::TPtr &event)
        : TJsonProxyBase<TRequestEvent, TResponseEvent>(event)
    {
    }

    TAutoPtr<TRequestEvent> PrepareRequest(const TActorContext &ctx) override
    {
        TAutoPtr<TRequestEvent> request = new TRequestEvent;
        NMon::TEvHttpInfo *msg = TBase::RequestEvent->Get();

        try {
            const auto &json = msg->Request.GetPostContent();
            if (json)
                request->Record = NProtobufJson::Json2Proto<typename TRequestEvent::ProtoRecordType>(json);
        } catch (yexception e) {
            TBase::ReplyWithErrorAndDie(TString("HTTP/1.1 400 Bad Request\r\n\r\nCan't parse provided JSON: ") + e.what(), ctx);
            return nullptr;
        }

        return request;
    }
};

template <typename TRequestEvent, typename TResponseEvent, bool useConsole>
class TJsonProxyCmsBase : public TJsonProxy<TRequestEvent, TResponseEvent> {
public:
    TJsonProxyCmsBase(NMon::TEvHttpInfo::TPtr &event)
        : TJsonProxy<TRequestEvent, TResponseEvent>(event)
    {
    }

    ui64 GetTabletId(const TActorContext &ctx) const override
    {
        auto dinfo = AppData(ctx)->DomainsInfo;
        ui32 domain = dinfo->Domains.begin()->first;
        return useConsole ? MakeConsoleID(domain) : MakeCmsID(domain);
    }

    TString GetTabletName() const override
    {
        return useConsole ? "Console" : "CMS";
    }
};

template <typename TRequestEvent, typename TResponseEvent>
using TJsonProxyCms = TJsonProxyCmsBase<TRequestEvent, TResponseEvent, false>;

template <typename TRequestEvent, typename TResponseEvent>
using TJsonProxyConsole = TJsonProxyCmsBase<TRequestEvent, TResponseEvent, true>;

} // NCms
} // NKikimr
