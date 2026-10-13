#ifndef SCN_STEP_ENEMY_ROLLBALL_PARAMDATA_H
#define SCN_STEP_ENEMY_ROLLBALL_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

// TODO: the name is a guess: nothing in the game names what Param::rollball() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[7];
    f32 mRadius[3];
};

}
}
}
}

#endif
