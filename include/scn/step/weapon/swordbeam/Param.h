#ifndef SCN_STEP_WEAPON_SWORDBEAM_PARAM_H
#define SCN_STEP_WEAPON_SWORDBEAM_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace swordbeam {

// TODO: name the members.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    u32 _14;
    gobj::MoveParamAccel _18;
};

}}}}  // namespace scn::step::weapon::swordbeam

#endif
