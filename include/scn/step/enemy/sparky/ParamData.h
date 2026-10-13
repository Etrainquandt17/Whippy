#ifndef SCN_STEP_ENEMY_SPARKY_PARAMDATA_H
#define SCN_STEP_ENEMY_SPARKY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sparky {

// TODO: the name is a guess: nothing in the game names what Param::sparky() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mJumpSpeedLow;
    f32 mJumpSpeedHigh;
    f32 mJumpSpeedH;
    int mHighJumpRate;
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    f32 mBodyRadius;
};

}
}
}
}

#endif
