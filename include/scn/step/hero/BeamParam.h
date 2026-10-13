#ifndef SCN_STEP_HERO_BEAMPARAM_H
#define SCN_STEP_HERO_BEAMPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::beam() returns it.
struct BeamParam {
    f32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
    u32 _10[3];
    u32 _1C;
    gobj::MoveParamDecel _20;
    u32 _24;
    u32 _28;
    u32 _2C;
    f32 _30;
    f32 _34;
    gobj::MoveParamDecel _38;
    gobj::MoveParamFall _3C;
    u32 _48;
    u32 _4C;
    f32 _50;
    f32 _54;
};

}}}  // namespace scn::step::hero

#endif
