#ifndef SCN_STEP_BOSS_UTILITY_H
#define SCN_STEP_BOSS_UTILITY_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/map/BinBossKind.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "scn/step/item/ShipPartKind.h"
#include "scn/step/sfx/CinemaScopeKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class Utility {
public:
    static bool IsHeroInRange(Boss& boss, f32 left, f32 right, f32 bottom, f32 top);
    static bool IsHatedHeroInRange(Boss& boss, f32 left, f32 right, f32 bottom, f32 top);
    static bool IsHeroUpper(Boss& boss, f32 height);
    static bool IsHeroSuper(Boss& boss);
    static bool IsHitWallFront(Boss& boss);
    static bool IsHitWallBack(Boss& boss);
    static bool IsFootStateGround(Boss& boss);
    static bool IsExistSuperElement(Boss& boss);
    static f32 GetHitPointRate(Boss& boss);
    static int GetLevel(Boss& boss);
    static bool IsVariationExtra(Boss& boss);
    static bool IsVariationBossRush(Boss& boss);
    static void GenerateStarEffect(Boss& boss, const hel::math::Vector2& pos, const hel::math::Vector2& speed, map::BinEnemyVariation variation,
                                   u32 count);
    static hel::math::Vector3 GetHatedHeroPos(Boss& boss);
    static bool IsArena(Boss& boss);
    static int GetRetryCount(Boss& boss);
    static void GenerateStarEffect(Boss& boss, const hel::math::Vector2& pos, const hel::math::Vector2& speed, map::BinEnemyVariation variation);
    static void GenerateStarEffect(Boss& boss, const hel::math::Vector2& pos, const hel::math::Vector2& speed, const hel::math::Vector2& accel,
                                   map::BinEnemyVariation variation);
    static void GenerateStarEffect(Boss& boss, const hel::math::Vector2& pos, const hel::math::Vector2& speed, const hel::math::Vector2& accel,
                                   map::BinEnemyVariation variation, u32 count);
    static void ControlHateOnAction(Boss& boss);
    static void TurnHatedHero(Boss& boss);
    static void StagingBossDamageL(Boss& boss);
    static void MintRegister(Boss& boss);
    static bool IsBossMBoss(map::BinBossKind kind);
    static void MintUnregister(Boss& boss);

    static bool IsStagingFirstAppear(Boss& boss);
    static void StagingFirstAppearStart(Boss& boss);
    static void StagingFirstAppearEnd(Boss& boss);
    static bool IsAppearDemoCancelRequested(Boss& boss);
    static void AppearBossPanel(Boss& boss);
    static void DisappearBossPanel(Boss& boss);
    static bool CanStartAppearance(Boss& boss, f32 distance);
    static bool CanStartAppearance(Boss& boss, f32 left, f32 right);
    static bool IsHeroDeadStop(Boss& boss);
    static bool IsStory(Boss& boss);
    static void GenerateShipParts(Boss& boss, item::ShipPartKind kind, const hel::math::Vector3& pos, const hel::math::Vector2& goal);
    static void StagingBossDead(Boss& boss, const hel::math::Vector3& offset);
    static void StagingBossDead(Boss& boss, const hel::math::Vector3& offset, u32 frame);
    static void StagingBossDead(Boss& boss, const hel::math::Vector3& offset, u32 frame, bool flag);
    static void StagingBossDeadCanDamageHero(Boss& boss, const hel::math::Vector3& offset);
    static void TurnMainHero(Boss& boss);
    static void TurnNearestHero(Boss& boss);
    static void CinemaScopeStart(Boss& boss, sfx::CinemaScopeKind kind);
    static void CinemaScopeStartNoAnim(Boss& boss, sfx::CinemaScopeKind kind);
    static void CinemaScopeEnd(Boss& boss);
    static void LockCameraOneScreen(Boss& boss, const hel::math::Vector2& center, f32 width, f32 height);
    static void LockCameraOneScreenQuick(Boss& boss, const hel::math::Vector2& center, f32 width, f32 height);
    static void DoNotMovePlayerWhenClear(Boss& boss);
    static void SetDamagePreventMikeAndCrash(Boss& boss);
};

}
}
}

#endif
