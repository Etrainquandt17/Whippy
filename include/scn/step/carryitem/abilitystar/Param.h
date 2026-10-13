#ifndef SCN_STEP_CARRYITEM_ABILITYSTAR_PARAM_H
#define SCN_STEP_CARRYITEM_ABILITYSTAR_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    u32 _10[13];
    u32 _44;
    u32 _48;
    u32 _4C;
    u32 _50;
    u32 _54;
    gobj::MoveParamFall _58;
};

}}}}  // namespace scn::step::carryitem::abilitystar

#endif
