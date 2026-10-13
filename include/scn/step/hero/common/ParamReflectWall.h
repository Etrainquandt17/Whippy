#ifndef SCN_STEP_HERO_COMMON_PARAMREFLECTWALL_H
#define SCN_STEP_HERO_COMMON_PARAMREFLECTWALL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

// TODO: names. The rates a damage state's speed is reflected with: floor, roof, wall, top of the view, sides of the view.
struct ParamReflectWall {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
};

}
}
}
}

#endif
