#ifndef SCN_STEP_HERO_FIREPARAM_H
#define SCN_STEP_HERO_FIREPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::fire() returns it.
struct FireParamBurningAccel {
    int _0;
    f32 _4[5];
};

struct FireParamBreathEffect {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C[4][2];
    f32 _2C[4];
};

struct FireParam {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    f32 _2C;
    f32 _30;
    f32 _34;
    u32 _38;
    f32 _3C;
    f32 _40;
    f32 _44;
    f32 _48;
    FireParamBurningAccel _4C;
    u32 _64;
    u32 _68;
    f32 _6C;
    f32 _70;
    f32 _74;
    u32 _78;
    u32 _7C;
    f32 _80;
    u32 _84;
    u32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    u32 _98;
    f32 _9C;
    f32 _A0;
    gobj::MoveParamFall _A4;
    gobj::MoveParamDecel _B0;
    int _B4;
    u32 _B8;
    u32 _BC;
    u32 _C0;
    gobj::MoveParamDecel _C4;
    f32 _C8;
    f32 _CC;
    f32 _D0;
    int _D4;
    int _D8;
    union {
        struct {
            f32 _DC;
            f32 _E0;
            f32 _E4;
        };
        FireParamBreathEffect _DCe;
    };
};

}
}
}

#endif
