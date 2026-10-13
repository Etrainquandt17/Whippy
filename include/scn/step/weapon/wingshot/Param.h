#ifndef SCN_STEP_WEAPON_WINGSHOT_PARAM_H
#define SCN_STEP_WEAPON_WINGSHOT_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace wingshot {

// TODO: name the members.
struct Param {
    f32 _0;
    f32 _4;
    u32 _8;
    gobj::MoveParamDecel _C;
};

}}}}  // namespace scn::step::weapon::wingshot

#endif
