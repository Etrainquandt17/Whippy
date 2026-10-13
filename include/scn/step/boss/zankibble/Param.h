#ifndef SCN_STEP_BOSS_ZANKIBBLE_PARAM_H
#define SCN_STEP_BOSS_ZANKIBBLE_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

// TODO: the name of the class is a guess; only what the script bindings read is known.
struct Param {
    // TODO: the names are guesses. Dash chooses between these two with ?:, and only accessors that return by value
    // make its branches write into one temporary as the original does.
    gobj::MoveParamAccel get58() const { return _58; }
    gobj::MoveParamAccel get64() const { return _64; }

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
    u32 _54;
    gobj::MoveParamAccel _58;
    gobj::MoveParamAccel _64;
    hel::math::Vec2 _70;
    hel::math::Vec2 _78;
    hel::math::Vec2 _80;
    hel::math::Vec2 mCutterStraightOffset;
    hel::math::Vec2 mCutterCircleOffset;
    f32 mCutterScaleStart;
    f32 mCutterScaleEnd;
    u32 mCutterScaleTime;
    hel::math::Vec2 mCutterBackCircleOffset;
    f32 mJumpAttackHeight;
    hel::math::Vec2 mCutterSlantOffset;
    hel::math::Vec2 mCutterSlantSpeed;
    hel::math::Vec2 _C0;
};

}}}}  // namespace scn::step::boss::zankibble

#endif
