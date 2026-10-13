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
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    u32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    gobj::MoveParamAccel _24;
    gobj::MoveParamDecel _30;
    gobj::MoveParamFall _34;
    u32 _40;
    u32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    f32 _60;
    f32 _64;
    u32 _68;
    u32 _6C;
    f32 _70;
    gobj::MoveParamAccel _74;
    gobj::MoveParamDecel _80;
    u32 _84[(0x90 - 0x84) / 4];
    u32 _90;
    f32 _94;
    f32 _98;
    gobj::MoveParamDecel _9C;
    gobj::MoveParamDecel _A0;
    gobj::MoveParamFall _A4;
    hel::math::Vec2 _B0;
    hel::math::Vec2 _B8;
    u32 _C0;
    f32 _C4;
    f32 _C8;
    f32 _CC;
    u32 _D0;
    f32 _D4;
    gobj::MoveParamAccel _D8;
};

}}}  // namespace scn::step::hero

#endif
