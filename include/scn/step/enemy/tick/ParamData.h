#ifndef SCN_STEP_ENEMY_TICK_PARAMDATA_H
#define SCN_STEP_ENEMY_TICK_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tick {

// TODO: the name is a guess: nothing in the game names what Param::tick() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mWaitFrame;
    f32 mJumpSpeed;
    gobj::MoveParamAccel mAccel;
    gobj::MoveParamFall mFall;
};

}
}
}
}

#endif
