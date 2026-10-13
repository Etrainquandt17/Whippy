#ifndef SCN_STEP_HERO_LEAFPARAM_H
#define SCN_STEP_HERO_LEAFPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names (the sub-structs are what the states' file-local param() functions return).
struct LeafParamBarrier {
    gobj::MoveParamAccel _0;
    f32 _C;
    u32 _10;
    u32 _14;
};

struct LeafParamDance {
    u32 _0;
    f32 _4;
    u32 _8;
    gobj::MoveParamDecel _C;
    gobj::MoveParamFall _10;
    gobj::MoveParamFall _1C;
};

struct LeafParamDisorderShot {
    f32 _0[8];
    u32 _20;
    f32 _24;
    f32 _28;
    f32 _2C;
    u32 _30;
};

// TODO: names and the other members. Param::leaf() returns it.
struct LeafParam {
    f32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
    LeafParamBarrier _10;
    LeafParamDance _28;
    u32 _50;
    LeafParamDisorderShot _54;
    u32 _88;
    u32 _8C;
};

}}}  // namespace scn::step::hero

#endif
