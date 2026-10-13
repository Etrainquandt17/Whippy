#ifndef SCN_STEP_WEAPON_LANDIASINGLEFIRERAIN_PARAM_H
#define SCN_STEP_WEAPON_LANDIASINGLEFIRERAIN_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefirerain {

// TODO: name the members.
struct Param {
    f32 _0;
    u32 _4;
    f32 _8;
    gobj::MoveParamDecel _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
};

}}}}  // namespace scn::step::weapon::landiasinglefirerain

#endif
