#include "scn/step/weapon/metalgeneralbitshot/Custom.h"

#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metalgeneralbitshot/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralbitshot {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().culling().setValid(false);
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x456), obj().location().pos());
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::metalgeneralbitshot
