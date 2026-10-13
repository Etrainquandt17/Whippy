#ifndef SCN_STEP_ENEMY_PLUID_PARAMDATA_H
#define SCN_STEP_ENEMY_PLUID_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

// TODO: the name is a guess: nothing in the game names what Param::pluid() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mHighJumpRate;
    f32 mJumpSpeedH;
    f32 mJumpSpeedV;
    f32 mHighJumpSpeedV;
    u32 mJumpStartFrame;
    u32 mJumpAnimFrame;
    u32 mStayFrameUnit;
    u32 mStayFallAnimFrame;
    gobj::MoveParamFall mStayFall;
};

}
}
}
}

#endif
