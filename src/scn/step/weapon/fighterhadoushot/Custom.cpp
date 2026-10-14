#include "scn/step/weapon/fighterhadoushot/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fighterhadoushot/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    switch (obj().variation()) {
    case 0:
        obj().stateChanger().setNextState<StateMain, Weapon*, Variation>(&obj(), VARIATION_0);
        break;
    case 1:
        obj().stateChanger().setNextState<StateMain, Weapon*, Variation>(&obj(), VARIATION_1);
        break;
    case 2:
        obj().stateChanger().setNextState<StateMain, Weapon*, Variation>(&obj(), VARIATION_2);
        break;
    }
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::fighterhadoushot
