#include "scn/step/weapon/grandlowperhole/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/grandlowperhole/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace grandlowperhole {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mIsMove(false) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::stop() {
    mIsMove = false;
}

void Custom::move() {
    mIsMove = true;
}

bool Custom::isMove() const {
    return mIsMove;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
