#ifndef SCN_STEP_WEAPON_KNUCKLEJOEHADOU_PARAM_H
#define SCN_STEP_WEAPON_KNUCKLEJOEHADOU_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace knucklejoehadou {

// TODO: name the members.
struct Param {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    gobj::MoveParamAccel _14;
    gobj::MoveParamFall _20;
};

}}}}  // namespace scn::step::weapon::knucklejoehadou

#endif
