#ifndef SCN_STEP_WEAPON_CUSTOMSIMPLE_H
#define SCN_STEP_WEAPON_CUSTOMSIMPLE_H

#include "scn/step/weapon/CustomBase.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

template <typename TState>
class CustomSimple : public CustomBase {
public:
    CustomSimple(Weapon& weapon) : CustomBase(weapon) {}

    virtual bool onInit() {
        obj().stateChanger().setNextState<TState, Weapon*>(&obj());
        return true;
    }
};

}
}
}

#endif
