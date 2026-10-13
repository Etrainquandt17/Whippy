#include "scn/step/weapon/hrd3eyelaser/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/hrd3eyelaser/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mLengthMax(40.0f) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setLengthMax(f32 length) {
    mLengthMax = length;
}

f32 Custom::getLengthMax() const {
    return mLengthMax;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
