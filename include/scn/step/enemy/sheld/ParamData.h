#ifndef SCN_STEP_ENEMY_SHELD_PARAMDATA_H
#define SCN_STEP_ENEMY_SHELD_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

// TODO: the name is a guess: nothing in the game names what Param::sheld() returns.
struct ParamData {
    u32 mJumpStartWait;
    f32 mJumpSpeedH;
    f32 mJumpSpeedV;
    gobj::MoveParamDecel mFallDecel;
    gobj::MoveParamFall mFall;
    f32 mDashFrameRate;
    u32 _20;
    u32 _24;
    f32 mDashAccel[3];
    f32 mChaseAccelMax[3];
    f32 mSmashedSpeedX;
    f32 mSmashedSpeedY;
    f32 mSmashedSpeedZ;
    f32 mSmashedRotSpeed;
    gobj::MoveParamDecel mSmashedDecel;
    gobj::MoveParamFall mSmashedFall;
    u32 mSmashedHitOnlyFrame;
    u32 mSmashedEndWait;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::sheld

#endif
