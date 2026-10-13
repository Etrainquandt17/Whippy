#ifndef SCN_STEP_BOSS_COMMON_PARAM_H
#define SCN_STEP_BOSS_COMMON_PARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

// TODO: the name of the class is a guess; only what the units written so far read is known.
struct Param {
    f32 mSuperHitPointRate;
    f32 mExtraHitPointRate;
    f32 mAngryHpRate;
    f32 mAngryHpRateExtra;
    u32 mDeadBent;
    u32 _14[11];
    hel::math::Vec2 mDeadEffectOffset;
};

}}}}  // namespace scn::step::boss::common

#endif
