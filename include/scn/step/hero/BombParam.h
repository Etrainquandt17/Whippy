#ifndef SCN_STEP_HERO_BOMBPARAM_H
#define SCN_STEP_HERO_BOMBPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::bomb() returns it.
struct BombParamCharge {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    u32 _1C;
    f32 _20;
    f32 _24;
    u32 _28;
};

struct BombParamThrow {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
};

struct BombParam {
    u32 _0;
    f32 _4;
    f32 _8;
    u32 _C;
    u32 _10;
    u32 _14[2];
    u32 _1C;
    BombParamCharge _20;
    BombParamThrow _4C;
    f32 _70;
    f32 _74;
    f32 _78;
    gobj::MoveParamDecel _7C;
    gobj::MoveParamFall _80;
};

}}}  // namespace scn::step::hero

#endif
