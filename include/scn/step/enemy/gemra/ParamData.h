#ifndef SCN_STEP_ENEMY_GEMRA_PARAMDATA_H
#define SCN_STEP_ENEMY_GEMRA_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

// TODO: the name is a guess: nothing in the game names what Param::gemra() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[4];
    u32 mFlyWaitFrame;
};

}
}
}
}

#endif
