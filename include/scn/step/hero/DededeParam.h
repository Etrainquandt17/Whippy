#ifndef SCN_STEP_HERO_DEDEDEPARAM_H
#define SCN_STEP_HERO_DEDEDEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names.
struct DededeParamSpin {
    f32 _0;
    gobj::MoveParamAccel _4;
    gobj::MoveParamDecel _10;
};
struct DededeParam {
    DededeParamSpin _0;
    DededeParamSpin _14;
    f32 _28;
    f32 _2C;
    f32 _30;
    f32 _34;
    int _38;
};

}
}
}

#endif
