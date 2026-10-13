#ifndef SCN_STEP_ENEMY_KABU_PARAMDATA_H
#define SCN_STEP_ENEMY_KABU_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

// TODO: the name is a guess: nothing in the game names what Param::kabu() returns.
struct ParamData {
    gobj::MoveParamAccel mAccelLevel0;
    gobj::MoveParamAccel mAccelLevel1;
    gobj::MoveParamAccel mAccelLevel2;
    gobj::MoveParamAccel mAccelLevel3;
    f32 mMoveFrameRate;
    f32 mMoveFrameRateJump;
    s32 mMoveJumpFrame;
    s32 mMoveJumpFrameStep;
    u32 mTurnWaitFrame;
    f32 mMoveAroundRange;
    f32 mJumpFallFrameRate;
    u32 mJumpStartFrame;
    f32 mJumpSpeedVStay;
    f32 mJumpSpeedV;
    f32 mJumpSpeedH;
    f32 mJumpSpeedVHigh;
    s32 mTeleportWaitFrame;
    s32 mTeleportWaitFrameStep;
    u32 mTeleportBlinkFrame;
    u32 mTeleportMoveFrame;
    f32 mBodyCollRadius;
    f32 mTeleportFloatSpeed;
    f32 mTeleportFloatAngleSpeed;
    f32 mTeleportDistXMin;
    f32 mTeleportDistXMax;
    f32 mTeleportDistYMin;
    f32 mTeleportDistYMax;
    s32 mJumpWaitTime;
    s32 mJumpWaitTimeStep;
    u32 _94;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}
}
}
}

#endif
