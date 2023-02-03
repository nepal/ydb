#pragma once

#include <library/cpp/actors/interconnect/interconnect_common.h>
#include <ydb/core/protos/config.pb.h>

class TCompatibilityInfo {
    friend class TCompatibilityInfoTest;
    using TOldFormat = NActors::TInterconnectProxyCommon::TVersionInfo;

public:
    struct TProtoConstructor {
        TProtoConstructor() = delete;

        struct TYdbVersion {
            std::optional<ui32> Year;
            std::optional<ui32> Major;
            std::optional<ui32> Minor;
            std::optional<ui32> Hotfix;

            NKikimrConfig::TYdbVersion ToPB() {
                NKikimrConfig::TYdbVersion res;
                if (Year) {
                    res.SetYear(*Year);
                }
                if (Major) {
                    res.SetMajor(*Major);
                }
                if (Minor) {
                    res.SetMinor(*Minor);
                }
                if (Hotfix) {
                    res.SetHotfix(*Hotfix);
                }

                return res;
            }
        };

        struct TCompatibilityRule {
            std::optional<std::string> Build;
            std::optional<TYdbVersion> BottomLimit;
            std::optional<TYdbVersion> UpperLimit;
            std::optional<ui32> ComponentId;
            std::optional<bool> Forbidden;

            NKikimrConfig::TCompatibilityRule ToPB() {
                NKikimrConfig::TCompatibilityRule res;
                if (Build) {
                    res.SetBuild(Build->data());
                }
                if (BottomLimit) {
                    res.MutableBottomLimit()->CopyFrom(BottomLimit->ToPB());
                }
                if (UpperLimit) {
                    res.MutableUpperLimit()->CopyFrom(UpperLimit->ToPB());
                }
                if (ComponentId) {
                    res.SetComponentId(*ComponentId);
                }
                if (Forbidden) {
                    res.SetForbidden(*Forbidden);
                }

                return res;
            }
        };

        struct TCurrentCompatibilityInfo {
            std::optional<std::string> Build;
            std::optional<TYdbVersion> YdbVersion;
            std::vector<TCompatibilityRule> CanLoadFrom;
            std::vector<TCompatibilityRule> StoresReadableBy;

            NKikimrConfig::TCurrentCompatibilityInfo ToPB() {
                NKikimrConfig::TCurrentCompatibilityInfo res;
                Y_VERIFY(Build);
                res.SetBuild(Build->data());
                if (YdbVersion) {
                    res.MutableYdbVersion()->CopyFrom(YdbVersion->ToPB());
                }

                for (auto canLoadFrom : CanLoadFrom) {
                    res.AddCanLoadFrom()->CopyFrom(canLoadFrom.ToPB());
                }
                for (auto storesReadableBy : StoresReadableBy) {
                    res.AddStoresReadableBy()->CopyFrom(storesReadableBy.ToPB());
                }

                return res;
            }
        };

        struct TStoredCompatibilityInfo {
            std::optional<std::string> Build;
            std::optional<TYdbVersion> YdbVersion;
            std::vector<TCompatibilityRule> ReadableBy;

            NKikimrConfig::TStoredCompatibilityInfo ToPB() {
                NKikimrConfig::TStoredCompatibilityInfo res;
                Y_VERIFY(Build);

                res.SetBuild(Build->data());
                if (YdbVersion) {
                    res.MutableYdbVersion()->CopyFrom(YdbVersion->ToPB());
                }

                for (auto readableBy : ReadableBy) {
                    res.AddReadableBy()->CopyFrom(readableBy.ToPB());
                }

                return res;
            }
        };
    };

public:
    TCompatibilityInfo() = delete;
    static const NKikimrConfig::TCurrentCompatibilityInfo* GetCurrent();
    static const NKikimrConfig::TStoredCompatibilityInfo* GetUnknown();

    static NKikimrConfig::TStoredCompatibilityInfo MakeStored(NKikimrConfig::TCompatibilityRule::EComponentId componentId);

    static bool CheckCompatibility(const NKikimrConfig::TStoredCompatibilityInfo* stored,
            ui32 componentId, TString& errorReason);
    static bool CheckCompatibility(const NKikimrConfig::TCurrentCompatibilityInfo* current,
            const NKikimrConfig::TStoredCompatibilityInfo* stored, ui32 componentId, TString& errorReason);

    static bool CheckCompatibility(const TOldFormat& stored, ui32 componentId, TString& errorReason);
    static bool CheckCompatibility(const NKikimrConfig::TCurrentCompatibilityInfo* current,
            const TOldFormat& stored, ui32 componentId, TString& errorReason);

    static NKikimrConfig::TStoredCompatibilityInfo MakeStored(ui32 componentId,
            const NKikimrConfig::TCurrentCompatibilityInfo* current);

private:
    static TSpinLock LockCurrent;
    static std::optional<NKikimrConfig::TCurrentCompatibilityInfo> CompatibilityInfo;
    static std::optional<NKikimrConfig::TStoredCompatibilityInfo> UnknownYdbRelease;

    // functions that modify compatibility information are only accessible from friend classes
    static void Reset(NKikimrConfig::TCurrentCompatibilityInfo* newCurrent);
};

// obsolete version control
// TODO: remove in the next major release
extern TMaybe<NActors::TInterconnectProxyCommon::TVersionInfo> VERSION;

void CheckVersionTag();
TString GetBranchName(TString url);
