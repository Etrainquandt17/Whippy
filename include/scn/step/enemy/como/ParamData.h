#ifndef SCN_STEP_ENEMY_COMO_PARAMDATA_H
#define SCN_STEP_ENEMY_COMO_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

// TODO: the name is a guess: nothing in the game names what Param::como() returns.
struct ParamData {
    u32 mAppearFrame;
    u32 mAppearWaitFrame;
    f32 mAppearLength;
    f32 mDiveAccel;
    f32 mDiveMaxSpeed;
    f32 mDiveBounceRate;
    f32 mDiveBounceEndSpeed;
    u32 mDiveWaitFrame;
    f32 mBackSpeed;
    u32 mBackSwingFrame;
    f32 mBackSwingLength;
    f32 mCutFallSpeed;
    gobj::MoveParamDecel mCutFallDecel;
    gobj::MoveParamFall mCutFallFall;
    u32 mCutLandingFrame;
    f32 mCutLandingViewOffsetY;
};

}}}}  // namespace scn::step::enemy::como

#endif
