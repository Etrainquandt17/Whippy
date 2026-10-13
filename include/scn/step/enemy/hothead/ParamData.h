#ifndef SCN_STEP_ENEMY_HOTHEAD_PARAMDATA_H
#define SCN_STEP_ENEMY_HOTHEAD_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

// TODO: the name is a guess: nothing in the game names what Param::hothead() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    int mAfterAttackFrame[3];
    f32 mNearDist;
};

}
}
}
}

#endif
