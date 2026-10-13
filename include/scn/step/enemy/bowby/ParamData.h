#ifndef SCN_STEP_ENEMY_BOWBY_PARAMDATA_H
#define SCN_STEP_ENEMY_BOWBY_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

// TODO: the name is a guess: nothing in the game names what Param::bowby() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mAreaNear;
    f32 mAreaFar;
    u32 _8[3];
    u32 mShotFrame;
};

}
}
}
}

#endif
