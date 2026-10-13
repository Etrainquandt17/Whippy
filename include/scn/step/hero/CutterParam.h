#ifndef SCN_STEP_HERO_CUTTERPARAM_H
#define SCN_STEP_HERO_CUTTERPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::cutter() returns it.
struct CutterParamThrow {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
};

struct CutterParamSlash {
    f32 _0;
    u32 _4;
    u32 _8;
};

struct CutterParam {
    f32 _0;
    u32 _4;
    u32 _8;
    gobj::MoveParamDecel _C;
    f32 _10;
    f32 _14;
    u32 _18;
    u32 _1C;
    u32 _20;
    CutterParamSlash _24;
    f32 _30;
    f32 _34;
    u32 _38;
    u32 _3C;
    f32 _40;
    f32 _44;
    u32 _48;
    gobj::MoveParamDecel _4C;
    gobj::MoveParamFall _50;
    gobj::MoveParamFall _5C;
    CutterParamThrow _68;
    f32 _7C;
    CutterParamThrow _80;
};

}}}  // namespace scn::step::hero

#endif
