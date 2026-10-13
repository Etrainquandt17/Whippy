#ifndef SCN_STEP_ENEMY_BLIPPER_PARAMDATA_H
#define SCN_STEP_ENEMY_BLIPPER_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

// TODO: the name is a guess: nothing in the game names what Param::blipper() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[5];
    f32 mJumpSpeedV[3];
    f32 mJumpSpeedH;
    f32 mFlyingOutSpeedV;
    f32 mDiveAccel;
    f32 mDiveSpeedMax;
    u32 mDiveTurnFrame;
    f32 mDiveWaterCheckY;
    u32 _38;
    gobj::MoveParamDecel mFattyBufferDecel;
    gobj::MoveParamFall mFattyBufferFall;
    f32 mFattyBufferAppearRotSpeed;
    u32 _50;
    hel::math::Vector3 mFattyBufferEscapeVelocity;
    f32 mFattyBufferEscapeVacuumOffHeight;
};

}}}}  // namespace scn::step::enemy::blipper

#endif
