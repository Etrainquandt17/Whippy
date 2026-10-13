#ifndef SCN_STEP_BOSS_WATERGALBOROS_PARAM_H
#define SCN_STEP_BOSS_WATERGALBOROS_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

struct Param {
    // TODO: the names are guesses; by-value accessors as in zankibble's Param.
    gobj::MoveParamAccel get84() const { return _84; }
    gobj::MoveParamAccel get90() const { return _90; }

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
    hel::math::Vec2 _48;
    hel::math::Vec2 _50;
    hel::math::Vec2 _58;
    hel::math::Vec2 _60;
    hel::math::Vec2 _68;
    hel::math::Vec2 mQuiveryOffset;
    hel::math::Vec2 mQuiverySpeed;
    u32 _80;
    gobj::MoveParamAccel _84;
    gobj::MoveParamAccel _90;
    hel::math::Vec2 _9C;
    hel::math::Vec2 _A4;
    hel::math::Vec2 _AC;
    f32 mCaptureSearchRadius;
    hel::math::Vec2 mCaptureSearchOffset;
    hel::math::Vec2 mCaptureSearchOffset2;
    u32 mCaptureAttackFrame;
    f32 mCaptureAttackSpeed;
    hel::math::Vec3 _D0;
    u32 mCaptureCount;
    u32 mCaptureDamageFirst;
    u32 mCaptureDamage;
    u32 mCaptureResistPower;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
