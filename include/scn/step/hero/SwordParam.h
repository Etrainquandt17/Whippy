#ifndef SCN_STEP_HERO_SWORDPARAM_H
#define SCN_STEP_HERO_SWORDPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names. Param::sword() returns it.
struct SwordParam {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    f32 _14;
    u32 _18;
    u32 _1C;
    f32 _20;
    f32 _24;
    u32 _28;
    u32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    u32 _40;
    f32 _44;
    u32 _48;
    u32 _4C;
    f32 _50;
    u32 _54;
    u32 _58;
    u32 _5C;
    u32 _60;
    f32 _64;
    f32 _68;
    f32 _6C;
    f32 _70;
    u32 _74;
    gobj::MoveParamDecel _78;
    gobj::MoveParamDecel _7C;
    gobj::MoveParamDecel _80;
    gobj::MoveParamDecel _84;
    u32 _88[3];
    u32 _94;
    gobj::MoveParamFall _98;
    f32 _A4;
    u32 _A8;
};

}
}
}

#endif
