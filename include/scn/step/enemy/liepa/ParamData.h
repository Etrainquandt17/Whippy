#ifndef SCN_STEP_ENEMY_LIEPA_PARAMDATA_H
#define SCN_STEP_ENEMY_LIEPA_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

// TODO: the name is a guess: nothing in the game names what Param::liepa() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    u32 mMoveWaitFrame;
    u32 mMoveAttackFrame;
    f32 mCircleRadius;
    u32 mCircleFrame;
    u32 mShotFrame;
    f32 mAttackAngle;
};

}
}
}
}

#endif
