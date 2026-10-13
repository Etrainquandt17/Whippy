#ifndef SCN_STEP_HERO_WHIPPARAM_H
#define SCN_STEP_HERO_WHIPPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::whip() returns it.
struct WhipParam {
    f32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    f32 _1C;
    gobj::MoveParamDecel _20;
    u32 _24;
    u32 _28;
    u32 _2C;
    f32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
    u32 _40;
    f32 _44;
    u32 _48;
    u32 _4C;
    u32 _50;
    u32 _54;
    u32 _58;
    u32 _5C;
};

}}}  // namespace scn::step::hero

#endif
