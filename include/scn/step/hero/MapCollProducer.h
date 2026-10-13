#ifndef SCN_STEP_HERO_MAPCOLLPRODUCER_H
#define SCN_STEP_HERO_MAPCOLLPRODUCER_H

#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace scn {
namespace step {
namespace hero {

// TODO: members, and the return type of chkOnFire is a guess.
class MapCollProducer {
public:
    bool chkOnFire(const hel::math::Vector2& pos, const hel::math::Vector2& dir, u32);
    void clear();
};

}
}
}

#endif
