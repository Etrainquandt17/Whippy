#ifndef SCN_STEP_ENEMY_DAMAGE_UTILITY_H
#define SCN_STEP_ENEMY_DAMAGE_UTILITY_H

#include "types.h"

namespace scn {
namespace step {

namespace chara {

class DamageInfo;

}

namespace enemy {

class Enemy;

namespace damage {

class Utility {
public:
    static void EmDamageUtility_InitTarget(Enemy* enemy);
    static void EmDamageUtility_InitVelocity(Enemy* enemy);
    static void EmDamageUtility_Move(Enemy* enemy);
    static bool EmDamageUtility_ReflectWall(Enemy* enemy);
    static void EmDamageUtility_ReqEffectHP0(Enemy* enemy);
    static void OnDamageStart(Enemy* enemy);
    static void OnDamageEnd(Enemy* enemy);
    static f32 EmDamageUtility_GetInitVelocityRate(Enemy* enemy, const chara::DamageInfo& info);
    static f32 EmDamageUtility_GetModelScale(Enemy* enemy);
    static f32 EmDamageUtility_GetEffectScale(Enemy* enemy);
    static f32 EmDamageUtility_GetEffectOffsetY(Enemy* enemy);
    static f32 EmDamageUtility_GetOCollOffsetY(Enemy* enemy);
    static void EmDamageUtility_DeadWithFreezeEffect(Enemy* enemy);
    static void EmDamageUtility_StopAnimRandomFrame(Enemy* enemy);
    static void UpdateMoveRate(Enemy* enemy);
    static void UpdateMoveRateExtreme(Enemy* enemy);
};

}
}
}
}

#endif
