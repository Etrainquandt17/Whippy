#ifndef SCN_STEP_ENEMY_BRONTOBURT_PARAMDATA_H
#define SCN_STEP_ENEMY_BRONTOBURT_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

// TODO: the name is a guess: nothing in the game names what Param::brontoburt() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mFlySpeed[4];
    f32 mFlyAccel[4];
    f32 mFlyRange;
    u32 mTakeOffFrame;
    f32 mTakeOffHeight;
    u32 mTakeOffWaitFrame;
    u32 mWhispyAppearFrame;
    u32 mWhispyWaitFrame;
    f32 mWhispyRotSpeed;
    f32 mWhispyDownHeight;
    f32 mWhispyUpHeight;
    gobj::MoveParamDecel mWhispyDecel;
    gobj::MoveParamFall mWhispyFall;
};

}
}
}
}

#endif
