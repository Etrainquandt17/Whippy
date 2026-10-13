#ifndef SCN_STEP_ENEMY_CARRYDEE_PARAMDATA_H
#define SCN_STEP_ENEMY_CARRYDEE_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

// TODO: the name is a guess: nothing in the game names what Param::carrydee() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[15];
    u32 mJumpFrame;
    f32 mJumpSpeedV;
    f32 mJumpSpeedH;
    gobj::MoveParamAccel mJumpAccel;
    gobj::MoveParamFall mJumpFall;
    f32 mCarryRangeH;
    f32 mCarryRangeV;
};

}
}
}
}

#endif
