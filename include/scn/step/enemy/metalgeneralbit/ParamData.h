#ifndef SCN_STEP_ENEMY_METALGENERALBIT_PARAMDATA_H
#define SCN_STEP_ENEMY_METALGENERALBIT_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

// TODO: the name is a guess: nothing in the game names what Param::metalgeneralbit() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    u32 mWaitFrameBase;
    u32 mWaitFrameRand;
    u32 mWaitFrameSuper;
    u32 _10[8];
    u32 mBeamFrame;
    u32 mDeadFrame;
};

}
}
}
}

#endif
