#ifndef SCN_STEP_HERO_WATERPARAM_H
#define SCN_STEP_HERO_WATERPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names.
struct WaterParamHover {
    f32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    gobj::MoveParamAccel _24;
    u32 _30[(0x48 - 0x30) / 4];
    gobj::MoveParamFall _48;
    f32 _54;
    f32 _58;
    f32 _5C;
};

// TODO: names, the members nothing written reads yet, and the size.
struct WaterParam {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    gobj::MoveParamFall _14;
    u32 _20;
    u32 _24;
    f32 _28;
    f32 _2C;
    f32 _30;
    f32 _34;
    f32 _38;
    u32 _3C;
    u32 _40;
    u32 _44;
    u32 _48[(0x9C - 0x48) / 4];
    f32 _9C;
    f32 _A0;
    u32 _A4;
    f32 _A8;
    u32 _AC;
    f32 _B0;
    f32 _B4;
    f32 _B8;
    f32 _BC;
    u32 _C0[(0xD8 - 0xC0) / 4];
    u32 _D8;
    f32 _DC;
    u32 _E0;
    u32 _E4[(0xF0 - 0xE4) / 4];
    f32 _F0;
    u32 _F4[(0x100 - 0xF4) / 4];
    WaterParamHover _100;
    u32 _160;
    f32 _164;
    f32 _168;
    u32 _16C;
    u32 _170[(0x188 - 0x170) / 4];
    f32 _188;
    f32 _18C;
    gobj::MoveParamDecel _190;
    f32 _194;
    f32 _198;
};

}}}  // namespace scn::step::hero

#endif
