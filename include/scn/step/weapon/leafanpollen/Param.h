#ifndef SCN_STEP_WEAPON_LEAFANPOLLEN_PARAM_H
#define SCN_STEP_WEAPON_LEAFANPOLLEN_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace leafanpollen {

// TODO: name the members; the one not seen in use yet is taken to be a word.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    f32 _14;
    f32 _18;
    u32 _1C;
    gobj::MoveParamDecel _20;
    gobj::MoveParamFall _24;
    gobj::MoveParamDecel _30;
    gobj::MoveParamFall _34;
};

}}}}  // namespace scn::step::weapon::leafanpollen

#endif
