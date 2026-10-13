#ifndef SCN_STEP_ENEMY_LOWPERBULLET_PARAMDATA_H
#define SCN_STEP_ENEMY_LOWPERBULLET_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

// TODO: the name is a guess: nothing in the game names what Param::lowperbullet() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mWaterMoveRate;
    gobj::MoveParamDecel mBombDecel;
    f32 _8;
    f32 mBombFallAccelStep;
    f32 _10;
    u32 mLandingFrame;
    f32 mBombFarDepthRate;
    f32 mBombFarCollDepth;
    f32 mBombFarMapCollDepth;
    gobj::MoveParamDecel mShotDecel;
    u32 mHomingFrame;
    gobj::MoveParamAccel mHomingAccel;
    gobj::MoveParamAccel mHomingAccelExtra;
    gobj::MoveParamDecel mHomingDecel;
    u32 _48[9];
    u32 mStillFrame;
    u32 mStillShakeFrame;
    u32 mStillMoveFrame;
};

}}}}  // namespace scn::step::enemy::lowperbullet

#endif
