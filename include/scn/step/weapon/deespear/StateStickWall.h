#ifndef SCN_STEP_WEAPON_DEESPEAR_STATESTICKWALL_H
#define SCN_STEP_WEAPON_DEESPEAR_STATESTICKWALL_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

// TODO: members and overrides; the unit is not written yet.
class StateStickWall : public StateBase {
public:
    StateStickWall(Weapon* weapon, f32 rot);
};

}
}
}
}

#endif
