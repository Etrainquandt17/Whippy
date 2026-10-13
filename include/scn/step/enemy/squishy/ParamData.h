#ifndef SCN_STEP_ENEMY_SQUISHY_PARAMDATA_H
#define SCN_STEP_ENEMY_SQUISHY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

// TODO: the name is a guess: nothing in the game names what Param::squishy() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamAccel mSwimAccel;
    gobj::MoveParamDecel mSwimDecel;
    f32 mSwimAccelStartFrame;
    f32 mSwimAccelEndFrame;
    f32 mWaterCheckOffsetY;
    f32 mSwimFrameRate;
    u32 _20;
    u32 mMoveInWaterFrameUp;
    u32 mMoveInWaterFrameDown;
    u32 mMoveInWaterAccelStartFrame;
    gobj::MoveParamAccel mMoveInWaterStayAccel;
    gobj::MoveParamFall mMoveInWaterStayFall;
    gobj::MoveParamAccel mMoveInWaterAccel;
    gobj::MoveParamFall mMoveInWaterFall;
    hel::math::Vector3 mOutWaterVelocity;
    u32 mMoveOnLandFrame;
    gobj::MoveParamAccel mMoveOnLandAccel;
    u32 mJumpStartFrame;
    u32 mJumpLandFrame[3];
    u32 mJumpWaterFrame;
    f32 mJumpFrameRate;
    f32 mJumpSpeedH;
    f32 mJumpSpeedV;
    f32 mJumpSpeedVStay;
    gobj::MoveParamDecel mAirDecel;
    gobj::MoveParamDecel mWaterDecel;
    gobj::MoveParamFall mFall;
    gobj::MoveParamFall mFallWater;
};

}
}
}
}

#endif
