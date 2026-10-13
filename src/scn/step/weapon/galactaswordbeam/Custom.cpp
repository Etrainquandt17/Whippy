#include "scn/step/weapon/galactaswordbeam/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactaswordbeam/StateFar.h"
#include "scn/step/weapon/galactaswordbeam/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactaswordbeam {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsReqStarEffect(true) {}

bool Custom::onInit() {
    if (obj().variation() == 1) {
        obj().stateChanger().setNextState<StateFar, Weapon*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    }
    return true;
}

void Custom::setIsReqStarEffect(bool isReq) {
    mIsReqStarEffect = isReq;
}

bool Custom::isReqStarEffect() const {
    return mIsReqStarEffect;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::galactaswordbeam
