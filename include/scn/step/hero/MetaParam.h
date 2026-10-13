#ifndef SCN_STEP_HERO_METAPARAM_H
#define SCN_STEP_HERO_METAPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names, and the size.
struct MetaParamSpin {
    gobj::MoveParamAccel _0;
    gobj::MoveParamDecel _C;
};

struct MetaParam {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    u32 _24;
    f32 _28;
    f32 _2C;
    u32 _30;
    u32 _34;
    f32 _38;
    f32 _3C;
    gobj::MoveParamDecel _40;
    gobj::MoveParamFall _44;
    gobj::MoveParamFall _50;
    u32 _5C;
    f32 _60;
    u32 _64;
    gobj::MoveParamDecel _68;
    gobj::MoveParamDecel _6C;
    gobj::MoveParamDecel _70;
    gobj::MoveParamDecel _74;
    MetaParamSpin _78;
    u32 _88;
    u32 _8C;
    f32 _90;
    f32 _94;
    f32 _98;
    u32 _9C;
    f32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
    u32 _B4;
    u32 _B8;
    f32 _BC;
    f32 _C0;
    f32 _C4;
    f32 _C8;
    f32 _CC;
    f32 _D0;
    f32 _D4;
    f32 _D8;
    f32 _DC;
    f32 _E0;
    f32 _E4;
    f32 _E8;
    f32 _EC;
    f32 _F0;
    f32 _F4;
    f32 _F8;
    gobj::MoveParamAccel _FC;
    gobj::MoveParamDecel _108;
};

}
}
}

#endif
