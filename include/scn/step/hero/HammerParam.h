#ifndef SCN_STEP_HERO_HAMMERPARAM_H
#define SCN_STEP_HERO_HAMMERPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names. Param::hammer() returns it.
struct HammerParamSpin {
    f32 _0;
    gobj::MoveParamAccel _4;
    gobj::MoveParamDecel _10;
};

struct HammerParam {
    HammerParamSpin _0;
    HammerParamSpin _14;
    f32 _28;
    f32 _2C;
    f32 _30;
    int _34;
};

}
}
}

#endif
