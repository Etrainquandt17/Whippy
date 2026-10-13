#ifndef SCN_STEP_BOSS_COMMON_COLLUTIL_H
#define SCN_STEP_BOSS_COMMON_COLLUTIL_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class CollUtil {
public:
    static void SetBodyCollDefault(Boss& boss, u32 id, f32 radius, hel::math::Vector2 offset);
    static void SetBodyCollDefault(Boss& boss, u32 id, f32 radius, hel::math::Vector2 offset, hel::math::Vector2 offset2);
};

}
}
}
}

#endif
