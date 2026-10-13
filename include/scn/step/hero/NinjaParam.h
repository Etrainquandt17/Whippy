#ifndef SCN_STEP_HERO_NINJAPARAM_H
#define SCN_STEP_HERO_NINJAPARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name, size and the other members; Param::ninja() returns it.
struct NinjaParam {
    u32 _0[0xB0 / 4];
    f32 _B0;
    f32 _B4;
};

}
}
}

#endif
