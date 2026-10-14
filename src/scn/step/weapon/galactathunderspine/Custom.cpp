#include "scn/step/weapon/galactathunderspine/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactathunderspine/StateAttack.h"
#include "scn/step/weapon/galactathunderspine/StateReady.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::galactathunderspine
