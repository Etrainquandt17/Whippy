#ifndef SCN_STEP_ENEMY_BULBY_PARAMDATA_H
#define SCN_STEP_ENEMY_BULBY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

// TODO: the name is a guess: nothing in the game names what Param::bulby() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mWaitFrame;
    u32 mHideFrame;
    f32 mJumpSpeed;
    f32 mJumpSpeedAttacker;
    f32 mShotSpeed;
    f32 mShotAngle;
    f32 mRangeH;
    f32 mRangeV;
    f32 mRangeVBuried;
    f32 mBodyRadiusBuried;
    f32 mBodyRadius;
    gobj::MoveParamDecel mDecel;
    gobj::MoveParamFall mFall;
    u32 mAttackShotFrame;
    hel::math::Vector2 mShotOffset;
};

}
}
}
}

#endif
