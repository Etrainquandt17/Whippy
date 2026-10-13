#ifndef SCN_STEP_HERO_ICEPARAM_H
#define SCN_STEP_HERO_ICEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name.
struct IceParamPush {
    gobj::MoveParamAccel _0;
    gobj::MoveParamDecel _C;
    gobj::MoveParamFall _10;
};

// TODO: names, the members nothing written reads yet, and the size.
struct IceParam {
    f32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
    u32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    u32 _24;
    u32 _28;
    IceParamPush _2C;
    f32 _48;
    u32 _4C;
    u32 _50;
    u32 _54;
    gobj::MoveParamDecel _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    u32 _68;
    u32 _6C;
    u32 _70;
    f32 _74;
    u32 _78;
    gobj::MoveParamDecel _7C;
    gobj::MoveParamDecel _80;
    u32 _84;
    u32 _88[(0x90 - 0x88) / 4];
    u32 _90[(0xA0 - 0x90) / 4];
    gobj::MoveParamDecel _A0;
    u32 _A4[3];
};

}}}  // namespace scn::step::hero

#endif
