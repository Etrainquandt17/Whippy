#ifndef SCN_STEP_HERO_FIGHTERPARAM_H
#define SCN_STEP_HERO_FIGHTERPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names, the members of the two sub-structs, and the size.
struct FighterParamShot {
    f32 _0;
    gobj::MoveParamDecel _4;
    gobj::MoveParamFall _8;
};

struct FighterParamThrow {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    gobj::MoveParamDecel _14;
    gobj::MoveParamFall _18;
};

struct FighterParam {
    u32 _0;
    u32 _4;
    f32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    f32 _2C;
    u32 _30;
    u32 _34;
    gobj::MoveParamDecel _38;
    gobj::MoveParamFall _3C;
    f32 _48;
    f32 _4C;
    u32 _50;
    f32 _54;
    f32 _58;
    u32 _5C;
    u32 _60;
    f32 _64;
    f32 _68;
    u32 _6C;
    u32 _70;
    f32 _74;
    f32 _78;
    f32 _7C;
    f32 _80;
    gobj::MoveParamDecel _84;
    gobj::MoveParamFall _88;
    gobj::MoveParamDecel _94;
    gobj::MoveParamFall _98;
    f32 _A4;
    gobj::MoveParamDecel _A8;
    f32 _AC;
    f32 _B0;
    gobj::MoveParamDecel _B4;
    gobj::MoveParamFall _B8;
    FighterParamShot _C4[3];
    FighterParamThrow _100[2];
    u32 _148;
    u32 _14C;
};

}
}
}

#endif
