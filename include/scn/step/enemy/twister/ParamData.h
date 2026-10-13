#ifndef SCN_STEP_ENEMY_TWISTER_PARAMDATA_H
#define SCN_STEP_ENEMY_TWISTER_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

// TODO: the name is a guess: nothing in the game names what Param::twister() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[11];
    gobj::MoveParamDecel mFallDecel;
    gobj::MoveParamFall mFall;
    f32 mRiseAccel;
    u32 _40[2];
    u32 mRiseFrame;
    u32 mRiseStartFrame;
    gobj::MoveParamAccel mRiseAccelH;
    gobj::MoveParamFall mRiseFall;
    f32 mThetaXMax;
    f32 mThetaYSpeed;
};

}
}
}
}

#endif
