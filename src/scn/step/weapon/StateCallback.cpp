#include "scn/step/weapon/StateCallback.h"

#include "scn/step/chara/LandConstraint.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

StateCallback::StateCallback(Weapon& weapon) : mObj(weapon) {}

void StateCallback::onStateChanged(const util::IStateChanger&) {
    mObj.landConstraint().resetMode();
}

}
}
}
