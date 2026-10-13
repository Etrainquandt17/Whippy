#ifndef SCN_STEP_ENEMY_TSUKIKAGE_PARAMDATA_H
#define SCN_STEP_ENEMY_TSUKIKAGE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

// TODO: the name is a guess: nothing in the game names what Param::tsukikage() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mJumpSpeedX;
    f32 mJumpSpeedY;
    f32 mJumpSpeedYHigh;
    gobj::MoveParamDecel mFallDecel;
    gobj::MoveParamFall mFall;
    u32 mJumpStartFrame;
    u32 mJumpAttackStartFrame;
    u32 mJumpAttackEndFrame;
    u32 mShurikenFrame;
    u32 _2c;
    f32 mShurikenOffsetX;
    f32 mShurikenOffsetY;
    f32 mShurikenSpeed;
    u32 _3c[(0x6c - 0x3c) / 4];
    f32 mJumpNearDistance;
    f32 mJumpAttackHeight;
    s32 mJumpAttackRand;
    s32 mJumpAttackRateHigh;
    s32 mJumpAttackRateLow;
    f32 mWallAttackRangeNear;
    f32 mWallAttackRangeFar;
    f32 mWallAttackRangeTop;
    f32 mWallAttackRangeBottom;
};

}}}}  // namespace scn::step::enemy::tsukikage

#endif
