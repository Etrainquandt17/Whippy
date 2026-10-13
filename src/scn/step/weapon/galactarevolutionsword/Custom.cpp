#include "scn/step/weapon/galactarevolutionsword/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactarevolutionsword/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactarevolutionsword {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mFloorPosY(0.0f) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setFloorPosY(f32 y) {
    mFloorPosY = y;
}

f32 Custom::getFloorPosY() const {
    return mFloorPosY;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
