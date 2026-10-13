#ifndef SCN_STEP_ENEMY_CLAYN_PARAMDATA_H
#define SCN_STEP_ENEMY_CLAYN_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

// TODO: the name is a guess: nothing in the game names what Param::clayn() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mHideWaitCount[3];
    u32 mWaitCount[3];
    f32 mRangeLeft;
    f32 mRangeRight;
    f32 mRangeV;
    u32 mAppearCollFrame;
    u32 mAppearReceiverFrame;
    u32 mDisappearCollFrame;
    u32 mDisappearReceiverFrame;
};

}
}
}
}

#endif
