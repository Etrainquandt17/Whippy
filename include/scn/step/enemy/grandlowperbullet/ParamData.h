#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_PARAMDATA_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

// TODO: the name is a guess: nothing in the game names what Param::grandlowperbullet() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mBombFrame;
    f32 mBombFallAccelStep;
    f32 _8;
    f32 _c;
    u32 mDivideFrame;
    u32 mDivideShakeFrame;
    f32 mDivideSpeed;
    u32 mHomingFrame;
};

}
}
}
}

#endif
