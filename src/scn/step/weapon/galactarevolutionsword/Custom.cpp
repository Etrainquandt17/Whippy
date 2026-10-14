#include "scn/step/weapon/galactarevolutionsword/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactarevolutionsword/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::galactarevolutionsword
