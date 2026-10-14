#include "scn/step/weapon/beamsuperball/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamsuperball/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace beamsuperball {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsSetMoveCenter(false), mMoveCenter() {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setMoveCenter(const Vector3& center) {
    mIsSetMoveCenter = true;
    mMoveCenter = center;
}

bool Custom::isSetMoveCenter() const {
    return mIsSetMoveCenter;
}

Vector3 Custom::getMoveCenter() const {
    return mMoveCenter;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::beamsuperball
