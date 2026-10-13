#ifndef SCN_STEP_BOSS_ENERGYSPHERECTRL_H
#define SCN_STEP_BOSS_ENERGYSPHERECTRL_H

#include "hel/geo/Rect.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

}
class Component;
namespace boss {

// TODO: members and the other functions.
class EnergySphereCtrl {
public:
    EnergySphereCtrl(Component& comp);
    ~EnergySphereCtrl();
    void setup(const hel::geo::Rect& rect);
    void pick();
    void setConstraintPos(const hel::math::Vector3& pos);
};

}
}
}

#endif
