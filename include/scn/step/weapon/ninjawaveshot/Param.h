#ifndef SCN_STEP_WEAPON_NINJAWAVESHOT_PARAM_H
#define SCN_STEP_WEAPON_NINJAWAVESHOT_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjawaveshot {

// TODO: name the members.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    u32 _14;
    u32 _18;
    gobj::MoveParamDecel _1C;
    u32 _20;
};

}}}}  // namespace scn::step::weapon::ninjawaveshot

#endif
