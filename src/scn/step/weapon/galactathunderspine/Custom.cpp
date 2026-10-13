#include "scn/step/weapon/galactathunderspine/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactathunderspine/StateAttack.h"
#include "scn/step/weapon/galactathunderspine/StateReady.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactathunderspine {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateReady, Weapon*>(&obj());
    return true;
}

void Custom::attack() {
    obj().stateChanger().setNextState<StateAttack, Weapon*>(&obj());
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
