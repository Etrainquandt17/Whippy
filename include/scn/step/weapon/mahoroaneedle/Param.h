#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_PARAM_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct Param {
    struct Attack {
        f32 _0;
        f32 _4;
        f32 _8;
    };

    u32 _0;
    u32 _4;
    u32 _8;
    Attack _C[3];
    Attack _30[3];
};

}}}}  // namespace scn::step::weapon::mahoroaneedle

#endif
