#ifndef SCN_STEP_HERO_WINGPARAM_H
#define SCN_STEP_HERO_WINGPARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::wing() returns it.
struct WingParam {
    u32 _0[0xB0 / 4];
    hel::math::Vec2 _B0;
    u32 _B8[(0xC4 - 0xB8) / 4];
    f32 _C4;
    f32 _C8;
    f32 _CC;
    u32 _D0;
    f32 _D4;
    gobj::MoveParamAccel _D8;
};

}
}
}

#endif
