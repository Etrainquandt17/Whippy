#ifndef SCN_STEP_ENEMY_SHOTZO_PARAMDATA_H
#define SCN_STEP_ENEMY_SHOTZO_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

// TODO: the name is a guess: nothing in the game names what Param::shotzo() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mAimFrame;
    u32 _4;
    f32 mShotSpeed;
    f32 mAimArea;
};

}
}
}
}

#endif
