#ifndef SCN_STEP_ENEMY_WAPOD_PARAMDATA_H
#define SCN_STEP_ENEMY_WAPOD_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

// TODO: the name is a guess: nothing in the game names what Param::wapod() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mPodRiseSpeed;
    f32 mRiseSpeed;
    f32 mStayHeight[3];
    u32 mPodWaitFrame;
};

}
}
}
}

#endif
