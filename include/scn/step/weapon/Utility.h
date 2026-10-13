#ifndef SCN_STEP_WEAPON_UTILITY_H
#define SCN_STEP_WEAPON_UTILITY_H

#include "hel/math/Vector2.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class Utility {
public:
    static void GenerateStarEffect(Weapon& weapon, const hel::math::Vector2& offset, const hel::math::Vector2& velocity, map::BinEnemyVariation variation);
    static void GenerateStarEffect(Weapon& weapon, const hel::math::Vector2& offset, const hel::math::Vector2& velocity, map::BinEnemyVariation variation, u32 num);
    static void GenerateStarEffectByPos(Weapon& weapon, const hel::math::Vector2& pos, const hel::math::Vector2& velocity, map::BinEnemyVariation variation);
    static void GenerateStarEffectByPos(Weapon& weapon, const hel::math::Vector2& pos, const hel::math::Vector2& velocity, map::BinEnemyVariation variation, u32 num);
    static void GenerateStarEffectFirstMapColl(
        Weapon& weapon, const hel::math::Vector2& offset, const hel::math::Vector2& velocity, const hel::math::Vector2& _3, map::BinEnemyVariation variation,
        u32 num
    );
    static void SetFollowerPos(const Weapon& weapon, Weapon& follower);
    static void SetFollowerNodePos(Weapon& weapon, Weapon& follower, u32 node);
    static void SetFollowerVisibility(Weapon& weapon, Weapon& follower);
    static void SetFollowerTarget(Weapon& weapon, Weapon& follower);
    static bool PenetrationWeaponMapCollHit(Weapon& weapon);
    static bool IsExtra(Weapon& weapon);
    static bool CheckShootingCulling(Weapon& weapon);
    static bool CheckShootingCulling(Weapon& weapon, f32 margin);
};

}
}
}

#endif
