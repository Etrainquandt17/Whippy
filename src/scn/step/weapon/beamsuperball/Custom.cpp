#include "scn/step/weapon/beamsuperball/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamsuperball/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace beamsuperball {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsSetMoveCenter(false), mMoveCenter() {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setMoveCenter(const hel::math::Vector3& center) {
    mIsSetMoveCenter = true;
    mMoveCenter = center;
}

bool Custom::isSetMoveCenter() const {
    return mIsSetMoveCenter;
}

hel::math::Vector3 Custom::getMoveCenter() const {
    return mMoveCenter;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
