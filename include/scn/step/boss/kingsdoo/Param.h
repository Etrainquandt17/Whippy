#ifndef SCN_STEP_BOSS_KINGSDOO_PARAM_H
#define SCN_STEP_BOSS_KINGSDOO_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

// TODO: the name of the class is a guess; only what the script bindings read is known.
struct Param {
    u32 mHitPoint[3];
    f32 _C;
    f32 _10;
    f32 _14;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    gobj::MoveParamDecel _24;
    gobj::MoveParamDecel _28;
    gobj::MoveParamFall _2C;
    hel::math::Vec2 _38;
    hel::math::Vec2 _40;
    gobj::MoveParamAccel _48;
    hel::math::Vec2 _54;
    hel::math::Vec2 _5C;
    f32 mJumpCenterHeight;
    f32 mJumpMachinegunHeight;
    u32 mJumpMachinegunTime;
    hel::math::Vec2 mMachinegunOffset;
    f32 mMachinegunRotMax;
    f32 mMachinegunRotSpeed;
    f32 mMachinegunAngleMin;
    f32 mMachinegunAngleMax;
    u32 _88;
    gobj::MoveParamAccel _8C;
    hel::math::Vec2 _98;
    hel::math::Vec2 _A0;
    hel::math::Vec2 _A8;
    hel::math::Vec2 mWaveShotOffset;
    f32 mWaveShotRecoil;
    f32 mWaveShotAngleMax;
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
