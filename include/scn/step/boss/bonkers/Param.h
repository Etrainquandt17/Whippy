#ifndef SCN_STEP_BOSS_BONKERS_PARAM_H
#define SCN_STEP_BOSS_BONKERS_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

// TODO: the name of the class is a guess, and so are the types of the members no unit reads.
struct Param {
    u32 mHitPoint[3];
    f32 _C;
    f32 _10;
    f32 _14;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    gobj::MoveParamDecel _24;
    gobj::MoveParamDecel _28;
    u32 _2C[3];
    hel::math::Vec2 mJumpBigStarPos;
    hel::math::Vec2 mJumpBigStarSpeed;
    gobj::MoveParamAccel _48;
    hel::math::Vec2 _54;
    hel::math::Vec2 _5C;
    gobj::MoveParamFall _64;
    u32 mJumpBigTime;
    f32 mJumpBigDistanceMax;
    f32 mJumpBigHeight;
    u32 mSwingTime;
    gobj::MoveParamAccel mSwingAccel;
    u32 mSwingPursuitTime;
    gobj::MoveParamAccel mSwingPursuitAccel;
    f32 mSwingPursuitReboundRate;
    u32 mSwingPursuitTurnWait;
    gobj::MoveParamDecel mSwingPursuitDecel;
    hel::math::Vec2 mSwingPursuitEffectOffset;
    f32 mSwingPursuitTurnDistance;
    gobj::MoveParamDecel _B4;
    hel::math::Vec2 mBombOffset;
    u32 _C0;
    u32 mRainBombNum;
    u32 mRainBombJumpTime;
    f32 mRainBombJumpHeight;
    u32 mRainBombWait;
    u32 mRainBombInterval;
    f32 mRainBombOffsetY;
    f32 mRainBombThrowOffsetY;
    f32 mRainBombSpeedCenter;
    f32 mRainBombSpeedSide;
    f32 mRainBombSpeedV;
};

}
}
}
}

#endif
