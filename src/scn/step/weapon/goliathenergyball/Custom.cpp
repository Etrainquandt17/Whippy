#include "scn/step/weapon/goliathenergyball/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mScaleUpFrame(1) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setScaleUpFrame(u32 frame) {
    mScaleUpFrame = frame;
}

u32 Custom::getScaleUpFrame() const {
    return mScaleUpFrame;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::goliathenergyball
