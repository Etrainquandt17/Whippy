#ifndef SCN_STEP_ENEMY_BOUNCY_PARAMDATA_H
#define SCN_STEP_ENEMY_BOUNCY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

// TODO: the name is a guess: nothing in the game names what Param::bouncy() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mJumpFallAccel;
    f32 mJumpFallMaxSpeed;
    f32 mJumpFallRate;
    f32 mWaitRecoverSpeedV;
    f32 mMoveRecoverSpeedH;
    f32 mMoveRecoverSpeedV;
    hel::math::Vector3 mEscapeVelocity;
    gobj::MoveParamDecel mEscapeDecel;
    gobj::MoveParamFall mEscapeFall;
    f32 mEscapeVacuumOffHeight;
};

}
}
}
}

#endif
