#ifndef SCN_STEP_HERO_LANDIAPARAM_H
#define SCN_STEP_HERO_LANDIAPARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names, the members nothing written reads yet, and the size.
struct LandiaParam {
    f32 _0;
    f32 _4;
    u32 _8;
    u32 _C;
    u32 _10[2];
    hel::math::Vec2 _18;
    f32 _20;
    f32 _24;
    f32 _28;
    u32 _2C;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
    u32 _40;
    u32 _44;
    u32 _48;
    u32 _4C;
    f32 _50;
    u32 _54;
    u32 _58;
    f32 _5C;
    u32 _60;
    f32 _64;
    u32 _68[(0x90 - 0x68) / 4];
    u32 _90[(0x98 - 0x90) / 4];
    u32 _98;
};

}}}  // namespace scn::step::hero

#endif
