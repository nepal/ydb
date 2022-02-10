#pragma once

#include "hive.h"
#include <ydb/core/protos/hive.pb.h>
#include <ydb/core/base/location.h>

namespace NKikimr {
namespace NHive {

struct TFollowerGroup {
    TFollowerGroupId Id = 0;
    bool AllowLeaderPromotion = false;
    bool AllowClientRead = false;
    bool RequireAllDataCenters = true;
    TVector<TNodeId> AllowedNodes;
    TVector<TDataCenterId> AllowedDataCenters;
    bool LocalNodeOnly = true; // run follower on the same node as leader
    bool RequireDifferentNodes = false; // do not run followers on same nodes as another followers of the same leader
    bool FollowerCountPerDataCenter = false; // PER_AZ KIKIMR-10443

    TFollowerGroup() = default;
    TFollowerGroup(const TFollowerGroup&) = delete;
    TFollowerGroup(TFollowerGroup&&) = delete;
    TFollowerGroup& operator =(const TFollowerGroup&) = delete;
    TFollowerGroup& operator =(TFollowerGroup&&) = delete;

    operator TFollowerGroupId() const {
        return Id;
    }

    TFollowerGroup& operator =(const NKikimrHive::TFollowerGroup& followerGroup) {
        FollowerCount = followerGroup.GetFollowerCount();
        AllowLeaderPromotion = followerGroup.GetAllowLeaderPromotion();
        AllowClientRead = followerGroup.GetAllowClientRead();
        RequireAllDataCenters = followerGroup.GetRequireAllDataCenters();
        {
            const auto& allowedNodes(followerGroup.GetAllowedNodeIDs());
            std::copy(allowedNodes.begin(), allowedNodes.end(), std::back_inserter(AllowedNodes));
        }
        {
            if (const auto& x = followerGroup.GetAllowedDataCenters(); !x.empty()) { 
                AllowedDataCenters.insert(AllowedDataCenters.end(), x.begin(), x.end()); 
            } else { 
                for (const auto& dataCenterId : followerGroup.GetAllowedDataCenterNumIDs()) { 
                    AllowedDataCenters.push_back(DataCenterToString(dataCenterId)); 
                } 
            } 
        }
        LocalNodeOnly = followerGroup.GetLocalNodeOnly();
        RequireDifferentNodes = followerGroup.GetRequireDifferentNodes();
        FollowerCountPerDataCenter = followerGroup.GetFollowerCountPerDataCenter();
        return *this;
    }

    ui32 GetRawFollowerCount() const {
        return FollowerCount;
    }

    ui32 GetComputedFollowerCount(ui32 dataCenters) const {
        if (FollowerCountPerDataCenter) {
            return FollowerCount * dataCenters;
        } else {
            return FollowerCount;
        }
    }

    void SetFollowerCount(ui32 followerCount) {
        FollowerCount = followerCount;
    }

private:
    ui32 FollowerCount = 0;
};

} // NHive
} // NKikimr
