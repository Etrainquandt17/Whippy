#ifndef SCN_STEP_ENEMY_BOMBMACHINEMISSILE_PARAMDATA_H
#define SCN_STEP_ENEMY_BOMBMACHINEMISSILE_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {

// TODO: the name is a guess: nothing in the game names what Param::bombmachinemissile() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSuperScale;
    u32 mLifeFrame;
    u32 mEffectFrame;
    u32 mEffectFrameSuper;
};

}
}
}
}

#endif
