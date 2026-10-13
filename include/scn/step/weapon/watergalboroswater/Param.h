#ifndef SCN_STEP_WEAPON_WATERGALBOROSWATER_PARAM_H
#define SCN_STEP_WEAPON_WATERGALBOROSWATER_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace watergalboroswater {

// TODO: name the members.
struct Param {
    f32 _0;
    u32 _4;
    gobj::MoveParamDecel _8;
    gobj::MoveParamFall _C;
};

}}}}  // namespace scn::step::weapon::watergalboroswater

#endif
