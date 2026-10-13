#ifndef SCN_STEP_WEAPON_FIGHTERKICKSHOT_PARAM_H
#define SCN_STEP_WEAPON_FIGHTERKICKSHOT_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterkickshot {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    f32 _0;
    u32 _4;
    gobj::MoveParamDecel _8;
    f32 _C;
    u32 _10;
};

}}}}  // namespace scn::step::weapon::fighterkickshot

#endif
