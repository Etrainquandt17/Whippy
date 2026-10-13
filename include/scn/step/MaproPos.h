#ifndef SCN_STEP_MAPROPOS_H
#define SCN_STEP_MAPROPOS_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {

// Returned in r3 and r4, so it has no constructor.
struct MaproPos {
    hel::math::Vector2 toWorldPos() const;

    u32 _0;
    u32 _4;
};

}}  // namespace scn::step

#endif
