#ifndef SCN_STEP_WEAPON_KINGSDOOWAVESHOT_PARAM_H
#define SCN_STEP_WEAPON_KINGSDOOWAVESHOT_PARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace kingsdoowaveshot {

// TODO: name the members.
struct Param {
    f32 mAttackRadius;
    f32 mAttackRadiusBig;
    u32 mLifeFrame;
    f32 _C;
    f32 _10;
    f32 _14;
    hel::math::Vec2 mStarOffset;
    hel::math::Vec2 mStarVelocity;
    hel::math::Vec2 mStarVelocity1;
    f32 mScaleBig;
    f32 _34;
    f32 _38;
    f32 _3C;
};

}}}}  // namespace scn::step::weapon::kingsdoowaveshot

#endif
