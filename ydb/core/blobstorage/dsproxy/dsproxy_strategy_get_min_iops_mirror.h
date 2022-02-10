#pragma once

#include "dsproxy_strategy_base.h"
#include "dsproxy_blackboard.h"

namespace NKikimr {

class TMinIopsMirrorStrategy : public TStrategyBase {
public:
    std::optional<EStrategyOutcome> RestoreWholeFromDataParts(TLogContext& /*logCtx*/, TBlobState &state, 
            const TBlobStorageGroupInfo &info) {
        TIntervalSet<i32> missing(state.Whole.NotHere);
        const ui32 totalPartCount = info.Type.TotalPartCount();
        for (auto it = missing.begin(); it != missing.end(); ++it) {
            auto [begin, end] = *it;
            for (ui32 partIdx = 0; partIdx < totalPartCount; ++partIdx) {
                TIntervalVec<i32> partInterval(begin, end);
                if (partInterval.IsSubsetOf(state.Parts[partIdx].Here)) {
                    TString tmp = TString::Uninitialized(end - begin);
                    Y_VERIFY(tmp.size());
                    state.Parts[partIdx].Data.Read(begin, const_cast<char*>(tmp.data()), tmp.size());
                    state.Whole.Data.Write(begin, tmp.data(), end - begin);
                    state.Whole.Here.Add(begin, end);
                    state.Whole.NotHere.Subtract(begin, end);
                }
            }
        }
        if (state.Whole.NotHere.IsEmpty()) {
            state.WholeSituation = TBlobState::ESituation::Present; 
            return EStrategyOutcome::DONE; 
        }
        return std::nullopt; 
    }

    EStrategyOutcome Process(TLogContext &logCtx, TBlobState &state, const TBlobStorageGroupInfo &info, 
            TBlackboard& /*blackboard*/, TGroupDiskRequests &groupDiskRequests) override { 
        if (auto res = RestoreWholeFromDataParts(logCtx, state, info)) { 
            return *res; 
        }
        // Look at the current layout and set the status if possible
        TBlobStorageGroupInfo::EBlobState pessimisticState = TBlobStorageGroupInfo::EBS_DISINTEGRATED;
        TBlobStorageGroupInfo::EBlobState optimisticState = TBlobStorageGroupInfo::EBS_DISINTEGRATED;
        TBlobStorageGroupInfo::EBlobState altruisticState = TBlobStorageGroupInfo::EBS_DISINTEGRATED;
        EvaluateCurrentLayout(logCtx, state, info, &pessimisticState, &optimisticState, &altruisticState, false);

        if (auto res = SetAbsentForUnrecoverableAltruistic(altruisticState, state)) { 
            return *res; 
        } else if (auto res = ProcessOptimistic(altruisticState, optimisticState, false, state)) { 
            return *res; 
        } else if (auto res = ProcessPessimistic(info, pessimisticState, false, state)) { 
            return *res; 
        }
 
        // Request minimal parts for each requested range of each blob 
        const ui32 totalPartCount = info.Type.TotalPartCount(); 
        const i32 handoff = info.Type.Handoff(); 
        bool isMinimalPossible = true; 
        for (auto it = state.Whole.NotHere.begin(); it != state.Whole.NotHere.end(); ++it) {
            auto [begin, end] = *it;
            bool isThereAGoodPart = false; 
            for (ui32 partIdx = 0; partIdx < totalPartCount; ++partIdx) { 
                TIntervalSet<i32> partInterval(begin, end);
                partInterval.Subtract(state.Parts[partIdx].Here); 
                if (!partInterval.IsEmpty()) { 
                    for (i32 niche = -1; niche < handoff; ++niche) { 
                        ui32 diskIdx = (niche < 0 ? partIdx : totalPartCount + niche); 
                        TBlobState::TDisk &disk = state.Disks[diskIdx]; 
                        TBlobState::ESituation partSituation = disk.DiskParts[partIdx].Situation; 
                        if (partSituation == TBlobState::ESituation::Unknown || 
                                partSituation == TBlobState::ESituation::Present) { 
                            isThereAGoodPart = true; 
                        } 
                    } 
                } 
            } 
            if (!isThereAGoodPart) { 
                isMinimalPossible = false; 
            } 
        }
        if (isMinimalPossible) { 
            for (auto it = state.Whole.NotHere.begin(); it != state.Whole.NotHere.end(); ++it) {
                auto [begin, end] = *it;
                for (ui32 partIdx = 0; partIdx < totalPartCount; ++partIdx) {
                    TIntervalSet<i32> partInterval(begin, end);
                    partInterval.Subtract(state.Parts[partIdx].Here);
                    if (!partInterval.IsEmpty()) {
                        for (i32 niche = -1; niche < handoff; ++niche) {
                            ui32 diskIdx = (niche < 0 ? partIdx : totalPartCount + niche);
                            TBlobState::TDisk &disk = state.Disks[diskIdx];
                            TBlobState::ESituation partSituation = disk.DiskParts[partIdx].Situation;
                            if (partSituation == TBlobState::ESituation::Unknown || 
                                    partSituation == TBlobState::ESituation::Present) { 
                                TIntervalSet<i32> unrequestedInterval(partInterval);
                                unrequestedInterval.Subtract(disk.DiskParts[partIdx].Requested); 
                                if (!unrequestedInterval.IsEmpty()) { 

                                    AddGetRequest(logCtx, groupDiskRequests, state.Id, partIdx, disk, 
                                            unrequestedInterval, "BPG45"); 
                                }
                            }
                        }
                    }
                }
            } 
        } else { 
            // It must be actually impossible to get the blob at all if we got here (or we have already sent 
            const ui32 totalPartCount = info.Type.TotalPartCount(); 
            for (ui32 diskIdx = 0; diskIdx < state.Disks.size(); ++diskIdx) { 
                bool isHandoff = (diskIdx >= totalPartCount); 
                ui32 beginPartIdx = (isHandoff ? 0 : diskIdx); 
                ui32 endPartIdx = (isHandoff ? totalPartCount : (diskIdx + 1)); 
                for (ui32 partIdx = beginPartIdx; partIdx < endPartIdx; ++partIdx) { 
                    TBlobState::TDisk &disk = state.Disks[diskIdx]; 
                    TBlobState::ESituation partSituation = disk.DiskParts[partIdx].Situation; 
                    if (partSituation == TBlobState::ESituation::Unknown || 
                            partSituation == TBlobState::ESituation::Present) { 
                        Y_VERIFY(false, "Inconsistent state# %s", state.ToString().data()); 
                    }
                }
            }
        }
        return EStrategyOutcome::IN_PROGRESS; 
    }
};

}//NKikimr
