#ifndef SCN_STEP_WEAPON_ROAHOAR_PARAM_H
#define SCN_STEP_WEAPON_ROAHOAR_PARAM_H

#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    f32 _20;
    u32 _24;
    u32 _28;
    f32 _2C;
    f32 _30;
    hel::math::Vec2 _34;
    f32 _3C;
    f32 _40;
};

}}}}  // namespace scn::step::weapon::roahoar

#endif
