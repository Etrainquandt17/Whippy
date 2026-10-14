#include "scn/step/weapon/metalgeneralpatriotfire/Custom.h"

#include "gobj/Target.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metalgeneralpatriotfire/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralpatriotfire {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().culling().setValid(false);
    switch (obj().variation()) {
    case 0:
    case 2:
        obj().target().setIsRightDir(false);
        break;
    case 1:
    case 3:
        obj().target().setIsRightDir(true);
        break;
    }
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::metalgeneralpatriotfire
