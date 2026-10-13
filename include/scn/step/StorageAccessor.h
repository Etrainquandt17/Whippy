#ifndef SCN_STEP_STORAGEACCESSOR_H
#define SCN_STEP_STORAGEACCESSOR_H

#include "scn/step/ChallengeKind.h"
#include "scn/step/LevelKind.h"
#include "scn/step/SphereUnlockKind.h"
#include "scn/step/StageKind.h"
#include "scn/step/map/BinGmkGeneralKind.h"
#include "scn/step/map/Kind.h"
#include "storage/StoryMode.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

class StorageAccessor {
public:
    static void BookingSave_AtCtrl();
    static void BookingSave_AtExit();
    static bool IsExistGmkCommon(Component& component, map::BinGmkGeneralKind kind, map::Kind mapKind, u32 index);
    static void AddGmkCommon(Component& component, map::BinGmkGeneralKind kind, map::Kind mapKind, u32 index);
    static bool IsExistOpenedPinata(Component& component, map::Kind mapKind, u16 index);
    static u16 IsOpenedPinataStriked(Component& component, map::Kind mapKind, u16 index);
    static void AddOpenedPinata(Component& component, map::Kind mapKind, u16 index, u16 striked);
    static bool GetStageOpened(Component& component, LevelKind level, u32 index);
    static bool GetLockShutterOpened(Component& component, u32 identNo);
    static void SetLockShutterOpened(Component& component, u32 identNo, bool isOpened);
    static bool GetIsSphereGet(Component& component, StageKind stage, u32 index);
    static bool GetSphereUnlockUnlocked(Component& component, SphereUnlockKind kind);
    static bool GetSphereUnlockEntered(Component& component, SphereUnlockKind kind);
    static bool GetSphereUnlockExecutedDemo(Component& component, SphereUnlockKind kind);
    static void SetSphereUnlockExecutedDemo(Component& component, SphereUnlockKind kind, bool executed);
    // TODO: the type it returns is not named anywhere; 1 to 4 are copper, silver, gold and platinum.
    static int GetChallengeStageMedalKind(Component& component, ChallengeKind kind);
    static bool GetWarpLowperEntered(Component& component, u32 index);
    static bool GetWarpLowperCleared(Component& component, u32 index);
    static void SetWarpLowperCleared(Component& component, u32 index, bool cleared);
    static LevelKind GetLevelLastCleared(Component& component);
    static bool GetLevelCleared(Component& component, LevelKind level);
    static bool GetLevelDemoFinished(Component& component, LevelKind level);
    static bool GetCompleteReserve(storage::StoryMode mode);
    static void SetCompleteReserve(storage::StoryMode mode, bool reserve);
};

}}  // namespace scn::step

#endif
