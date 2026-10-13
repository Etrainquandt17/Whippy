#ifndef SCN_STEP_ENEMY_STARMAN_PARAMDATA_H
#define SCN_STEP_ENEMY_STARMAN_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

// TODO: the name is a guess: nothing in the game names what Param::starman() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mHighJumpRange;
    u32 mJumpStartFrame;
    u32 mHighJumpStartFrame;
    f32 mJumpSpeed;
    f32 mHighJumpSpeed;
    f32 mAttackRadius;
    f32 mAttackOffsetY;
    gobj::MoveParamAccel mFlyAccel[3];
    u32 mFlyFrame;
    f32 mFlyStopDist;
    f32 mFlySinWidth;
    f32 mFlySinSpeed;
    f32 mStraightSpeedY;
    f32 mStraightStartX;
    f32 mStraightStartY;
    f32 mStraightRiseAccel;
    f32 mStraightRiseMax;
    u32 mStraightStartFrame;
    u32 mStraightRiseFrame;
    gobj::MoveParamFall mFall;
};

}
}
}
}

#endif
