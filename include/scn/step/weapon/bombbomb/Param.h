#ifndef SCN_STEP_WEAPON_BOMBBOMB_PARAM_H
#define SCN_STEP_WEAPON_BOMBBOMB_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    u32 _0[0x9C / 4];
    u32 _9C;
    u32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    u32 _B0;
};

}}}}  // namespace scn::step::weapon::bombbomb

#endif
