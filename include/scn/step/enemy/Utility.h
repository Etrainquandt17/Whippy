#ifndef SCN_STEP_ENEMY_UTILITY_H
#define SCN_STEP_ENEMY_UTILITY_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: the other functions.
class Utility {
public:
    static f32 GetModelScaleBySizeType(const Enemy& enemy);
    static bool IsNearestPlayerRight(Enemy& enemy);
    static void SetTargetByDirType(Enemy& enemy);
    static f32 GetRotByDirType(Enemy& enemy);
    static hel::math::Vector3 GetDirVecByDirType(Enemy& enemy);
    static bool IsFixDirType(Enemy& enemy);
    static bool IsCameraOut(Enemy& enemy);
    static bool CheckShootingCulling(Enemy& enemy);
    static bool IsPlayerExist(Enemy& enemy);
    static void Turn(Enemy& enemy);
    static bool ChkCliff(Enemy& enemy);
    static void ChkCliffTurn(Enemy& enemy);
    static void ChkNururiTurn(Enemy& enemy);
    static void TurnHero(Enemy& enemy);
    static void Suicide(Enemy& enemy);
    static bool IsHeroInRange(Enemy& enemy, f32 left, f32 right, f32 top, f32 bottom);
    static bool IsHeroInRangeByDir(Enemy& enemy, f32 front, f32 back, f32 top, f32 bottom);
    static bool IsExistLand(Enemy& enemy, f32 x, f32 y);
    static bool IsWaterGrid(Enemy& enemy, f32 x, f32 y);
    static bool IsExistKeyCarryingHero(Enemy& enemy);
    static bool IsExtra(const Enemy& enemy);
    static hel::math::Vector2 GetNearestPlayerPos(Enemy& enemy);
    static hel::math::Vector3 GetCenterPos(const Enemy& enemy);
    static u32 GetAdditionalVacuumFrameBySizeType(const Enemy& enemy);
    static void HitFloorCheck(Enemy& enemy);
    static void SetCustomMtxRotate(Enemy& enemy, const hel::math::Vector3& rot);
    static bool ChkNururiByDir(Enemy& enemy, f32 dist);
    static hel::math::Vector3 GetDefaultCenterOffset(const Enemy& enemy);
};

}
}
}

#endif
