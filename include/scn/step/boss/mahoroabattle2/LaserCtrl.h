#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_LASERCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_LASERCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {

namespace weapon {

// TODO: this belongs in a header of scn/step/weapon, which has none yet; only the value used here is known.
enum Kind {
    Kind_9C = 0x9c,
};

}

namespace boss {
namespace mahoroabattle2 {

// TODO: members.
class LaserCtrl {
public:
    void request(weapon::Kind kind, u32 _2, const hel::math::Vector3& _3, const hel::math::Vector3& _4, u32 _5, u32 _6, f32 _7,
                 bool _8);
};

}
}
}
}

#endif
