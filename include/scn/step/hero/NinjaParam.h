#ifndef SCN_STEP_HERO_NINJAPARAM_H
#define SCN_STEP_HERO_NINJAPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name, size and the other members; Param::ninja() returns it.
struct NinjaParam {
    u32 _0;
    u32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    u32 _14[(0x28 - 0x14) / 4];
    f32 _28;
    gobj::MoveParamDecel _2C;
    f32 _30;
    f32 _34;
    u32 _38;
    u32 _3C;
    f32 _40;
    f32 _44;
    u32 _48;
    u32 _4C;
    f32 _50;
    u32 _54;
    u32 _58;
    gobj::MoveParamDecel _5C;
    f32 _60;
    gobj::MoveParamDecel _64;
    u32 _68;
    u32 _6C;
    u32 _70;
    f32 _74;
    f32 _78;
    f32 _7C;
    f32 _80;
    f32 _84;
    u32 _88;
    f32 _8C;
    f32 _90;
    f32 _94;
    u32 _98;
    u32 _9C;
    u32 _A0;
    u32 _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
    f32 _B4;
    u32 _B8;
};

}}}  // namespace scn::step::hero

#endif
