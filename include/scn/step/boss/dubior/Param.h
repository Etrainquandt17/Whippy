#ifndef SCN_STEP_BOSS_DUBIOR_PARAM_H
#define SCN_STEP_BOSS_DUBIOR_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

// TODO: the name of the class is a guess, and so are the types of the members no unit reads.
struct Param {
    u32 mHitPoint[3];
    f32 _C;
    f32 _10;
    f32 _14;
    f32 mBodyCollRadius;
    hel::math::Vec2 mBodyCollOffset;
    hel::math::Vec2 mBodyCollOffset2;
    f32 mFastMoveCollRadius;
    hel::math::Vec2 mFastMoveCollOffset;
    f32 mDashCollRadius;
    hel::math::Vec2 mDashCollOffset;
    hel::math::Vec2 mDashCollOffset2;
    gobj::MoveParamDecel _4C;
    u32 _50[3];
    f32 mHeightAdjustDistance;
    f32 mFirstOffsY;
    f32 mHeightHigh;
    f32 mMoveWaveRange;
    f32 mMoveWaveOffset;
    hel::math::Vec2 mCallOffset;
    hel::math::Vec2 mCallOffset2;
    f32 mCallSpace;
    u32 mHeightAdjustTime;
    f32 mDashBackSpeed;
    gobj::MoveParamDecel mDashDecel;
    gobj::MoveParamAccel mDashAccel;
    hel::math::Vec2 mDashWallHitStarPos;
    hel::math::Vec2 mDashWallHitStarSpeed;
    u32 _AC[10];
    f32 mThunderRandRange;
    f32 mThunderOffsetY;
    u32 mMoveThunderStartTime;
    u32 mMoveThunderTime;
    u32 mMoveThunderAcrossTime;
    f32 mMoveThunderOffsetX;
    f32 mMoveThunderHeight;
    f32 mMoveThunderDistance;
    f32 mMoveThunderWave;
    hel::math::Vec2 mShotOffset;
    f32 mShotSpeed;
};

}
}
}
}

#endif
