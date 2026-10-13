#ifndef SCN_STEP_ENEMY_DOUBTERSNAKE_PARAMDATA_H
#define SCN_STEP_ENEMY_DOUBTERSNAKE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

// TODO: the name is a guess: nothing in the game names what Param::doubtersnake() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mAppearFrameRate;
    u32 mAppearCollFrame;
    gobj::MoveParamDecel mAppearDecel;
    gobj::MoveParamFall mAppearFall;
    f32 mWalkAngleSpeed;
    f32 mWalkAccelAdd;
    gobj::MoveParamAccel mWalkAccel;
    f32 mJumpFrameRate;
    f32 mJumpSpeedH;
    f32 mJumpSpeedHHard;
    f32 mJumpSpeedV;
    gobj::MoveParamDecel mJumpDecel;
    gobj::MoveParamFall mJumpFall;
    f32 mEscapeSpeedZ;
    f32 mEscapeAngleSpeed;
    u32 mEscapeJumpFrame;
    f32 mEscapeJumpSpeed;
    f32 mEscapeFrameRate;
    f32 mEscapeZ;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    gobj::MoveParamFall mEscapeJumpFall;
};

}
}
}
}

#endif
