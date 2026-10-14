#include "scn/step/weapon/goliathenergyball/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/goliathenergyball/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::goliathenergyball
