#ifndef SCN_STEP_WEAPON_NEEDLESHOT_PARAM_H
#define SCN_STEP_WEAPON_NEEDLESHOT_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    f32 _0;
    f32 _4;
    u32 _8;
    u32 _C;
    f32 _10;
    f32 _14;
    u32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    f32 _2C;
    f32 _30;
    f32 _34;
    gobj::MoveParamDecel _38;
    gobj::MoveParamFall _3C;
    u32 _48;
};

}}}}  // namespace scn::step::weapon::needleshot

#endif
