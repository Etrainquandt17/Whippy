#ifndef SCN_STEP_ENEMY_POPPYBROJRBOMB_PARAMDATA_H
#define SCN_STEP_ENEMY_POPPYBROJRBOMB_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojrbomb {

// TODO: the name is a guess: nothing in the game names what Param::poppybrojrbomb() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[3];
    f32 mExplosionOffsetY;
};

}
}
}
}

#endif
