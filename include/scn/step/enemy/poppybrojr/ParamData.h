#ifndef SCN_STEP_ENEMY_POPPYBROJR_PARAMDATA_H
#define SCN_STEP_ENEMY_POPPYBROJR_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

// TODO: the name is a guess: nothing in the game names what Param::poppybrojr() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[7];
    u32 mThrowFrame;
    f32 mThrowSpeedX;
    f32 mThrowSpeedY;
};

}
}
}
}

#endif
