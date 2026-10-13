#ifndef SCN_STEP_ENEMY_LEAFAN_PARAMDATA_H
#define SCN_STEP_ENEMY_LEAFAN_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

// TODO: the name is a guess: nothing in the game names what Param::leafan() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    f32 mJumpSpeed;
    gobj::MoveParamAccel mJumpAccel;
    gobj::MoveParamFall mJumpFall;
    u32 mAttackShotFrame;
    f32 mWeaponSpeed;
};

}
}
}
}

#endif
