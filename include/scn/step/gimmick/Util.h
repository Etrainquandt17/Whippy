#ifndef SCN_STEP_GIMMICK_UTIL_H
#define SCN_STEP_GIMMICK_UTIL_H

#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace scn {
namespace step {

class Component;

namespace gimmick {

class Util {
public:
    static bool InScreen(Component& component, const hel::math::Vector2& pos, f32 margin);
};

}
}
}

#endif
