#ifndef SCN_STEP_ENEMY_METALGENERALBOMB_PARAMDATA_H
#define SCN_STEP_ENEMY_METALGENERALBOMB_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {

// TODO: the name is a guess: nothing in the game names what Param::metalgeneralbomb() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    f32 mRotSpeed;
    u32 mBlinkFrame;
    u32 mExplodeFrame;
};

}
}
}
}

#endif
