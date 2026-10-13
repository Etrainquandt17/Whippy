#ifndef SCN_STEP_WEAPON_ROAHBULLET_PARAM_H
#define SCN_STEP_WEAPON_ROAHBULLET_PARAM_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vec3.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    f32 _0;
    f32 _4;
    u32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    u32 _18;
    u32 _1C;
    gobj::MoveParamAccel _20;
    u32 _2C;
    u32 _30;
    u32 _34;
    hel::math::Vec2 _38;
    u32 _40;
    u32 _44;
    hel::math::Vec3 _48;
    f32 _54;
    u32 _58;
    f32 _5C;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
