#include "scn/step/weapon/metalgeneralneedle/Custom.h"

#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metalgeneralneedle/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralneedle {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x464), obj().location().pos());
    obj().comp().permSoundSE().start(0x3E5);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::metalgeneralneedle
