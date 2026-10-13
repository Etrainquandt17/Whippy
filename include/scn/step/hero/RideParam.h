#ifndef SCN_STEP_HERO_RIDEPARAM_H
#define SCN_STEP_HERO_RIDEPARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name, size and the other members; Param::ride() returns it.
struct RideParam {
    u32 _0[0x30 / 4];
    f32 _30;
    f32 _34;
    f32 _38;
};

}}}  // namespace scn::step::hero

#endif
