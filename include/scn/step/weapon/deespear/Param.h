#ifndef SCN_STEP_WEAPON_DEESPEAR_PARAM_H
#define SCN_STEP_WEAPON_DEESPEAR_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    gobj::MoveParamDecel _10;
    gobj::MoveParamFall _14;
    u32 _20;
    u32 _24;
    u32 _28;
    u32 _2C;
    u32 _30;
    f32 _34;
    f32 _38;
    f32 _3C;
    u32 _40;
    u32 _44;
};

}}}}  // namespace scn::step::weapon::deespear

#endif
