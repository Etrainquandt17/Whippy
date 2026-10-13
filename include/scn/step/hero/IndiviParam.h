#ifndef SCN_STEP_HERO_INDIVIPARAM_H
#define SCN_STEP_HERO_INDIVIPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: size, and the members that no state has read yet (padding stands in for them).
struct IndiviParam {
    u32 _pad0[0x48 / 4];
    f32 _48;
    gobj::MoveParamAccel _4C;
    gobj::MoveParamFall _58;
};

}
}
}

#endif
