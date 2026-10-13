#ifndef SCN_STEP_HERO_PARASOLPARAM_H
#define SCN_STEP_HERO_PARASOLPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace parasol {

struct ParamSwingAttack {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
};

struct ParamBarrier {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
};

}

// TODO: names and the members between these. Param::parasol() returns it.
struct ParasolParam {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    gobj::MoveParamDecel _10;
    gobj::MoveParamFall _14;
    gobj::MoveParamDecel _20;
    gobj::MoveParamFall _24;
    u32 _30;
    f32 _34;
    gobj::MoveParamDecel _38;
    gobj::MoveParamFall _3C;
    f32 _48;
    f32 _4C;
    u32 _50;
    gobj::MoveParamAccel _54;
    gobj::MoveParamDecel _60;
    gobj::MoveParamFall _64;
    f32 _70;
    f32 _74;
    u32 _78;
    gobj::MoveParamAccel _7C;
    gobj::MoveParamDecel _88;
    gobj::MoveParamFall _8C;
    f32 _98;
    f32 _9C;
    parasol::ParamBarrier _A0;
    parasol::ParamBarrier _C4;
    parasol::ParamSwingAttack _E8[5];
    f32 _160;
    f32 _164;
    gobj::MoveParamAccel _168;
    gobj::MoveParamDecel _174;
    gobj::MoveParamFall _178;
};

}
}
}

#endif
