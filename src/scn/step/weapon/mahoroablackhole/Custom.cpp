#include "scn/step/weapon/mahoroablackhole/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroablackhole/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsRequestedChangeStateToEnd(false) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::reqChangeStateToEnd() {
    mIsRequestedChangeStateToEnd = true;
}

bool Custom::isRequestedChangeStateToEnd() const {
    return mIsRequestedChangeStateToEnd;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroablackhole
