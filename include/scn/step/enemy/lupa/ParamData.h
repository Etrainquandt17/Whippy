#ifndef SCN_STEP_ENEMY_LUPA_PARAMDATA_H
#define SCN_STEP_ENEMY_LUPA_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

// TODO: the name is a guess: nothing in the game names what Param::lupa() returns. Whatever follows the last
// member is not known yet.
struct ParamData {
    gobj::MoveParamAccel mMoveAccel;
    gobj::MoveParamDecel mWaitDecel;
    f32 mRotIntpRate;
    f32 mShapeWidth;
    f32 mShapeBottom;
    f32 mShapeTop;
    f32 mLandCheckWidth;
    f32 mLandCheckHeight;
    f32 mApproachSpeed;
    f32 mMoveRangeFar;
    f32 mMoveRange;
    u32 mAttackWaitLv0;
    u32 mAttackWaitLv1;
    u32 mAttackWaitLv2;
    u32 mWaitAttackShotFrame;
};

}
}
}
}

#endif
