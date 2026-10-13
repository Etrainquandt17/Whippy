#ifndef SCN_STEP_ENEMY_ROCKY_PARAMDATA_H
#define SCN_STEP_ENEMY_ROCKY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

// TODO: the name is a guess: nothing in the game names what Param::rocky() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    s32 mAttackWait;
    s32 mCliffAttackWait;
    f32 mCliffJumpSpeedH;
    f32 mCliffJumpSpeedV;
    s32 mCliffJumpStopFrame;
    s32 mCliffJumpFallFrame;
    gobj::MoveParamFall mCliffJumpFall;
    f32 mFallSpeedUpSpeedV;
    gobj::MoveParamFall mFallSpeedUp;
    gobj::MoveParamFall mFall;
    f32 mJumpSpeedV;
    u32 _44;
    u32 _48;
    s32 mJumpStopFrame;
    f32 mJumpSpeedH;
    s32 mJumpFallFrame;
    gobj::MoveParamFall mJumpFall;
    f32 mLandingSlopeNormalX;
    f32 mLandingEffectOffsetX;
    f32 mLandingEffectOffsetY;
    f32 mSlopeSpeed;
    gobj::MoveParamDecel mSlopeDecel;
    f32 mSlopeStayNormalX;
    s32 mStayRandFrame;
    s32 mStayBaseFrame;
    s32 mStayAttackWait;
    f32 mWalkSpeed;
    s32 mWalkMoveFrame[4];
    s32 mWalkRandFrame;
    s32 mWalkBaseFrame;
    s32 mWalkAttackWait;
    f32 mWalkFrameRate;
    gobj::MoveParamDecel mWalkDecel;
    f32 mWalkSlopeNormalX;
    f32 mStayAttackRangeX;
    f32 mStayAttackRangeTop;
    f32 mStayAttackRangeBottom;
    f32 mBodyCollRadius;
};

}}}}  // namespace scn::step::enemy::rocky

#endif
