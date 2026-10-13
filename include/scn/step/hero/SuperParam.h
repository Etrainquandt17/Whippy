#ifndef SCN_STEP_HERO_SUPERPARAM_H
#define SCN_STEP_HERO_SUPERPARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names. Param::super() returns it; super::Utility::Param() picks one of _64 by the ability.
struct SuperParamAbility {
    u32 _0;
    f32 _4;
};

struct SuperParam {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    u32 _14[20];
    SuperParamAbility _64[5];
};

}
}
}

#endif
