#include "scn/step/weapon/gianttornado/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/gianttornado/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace gianttornado {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
