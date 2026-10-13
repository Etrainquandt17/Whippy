#include "scn/step/weapon/mahoroablackhole/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroablackhole/StateMain.h"

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

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
