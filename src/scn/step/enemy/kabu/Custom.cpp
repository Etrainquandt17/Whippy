#include "scn/step/enemy/kabu/Custom.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/kabu/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsInvisible(false) {}

bool Custom::onInWater() {
    if (!mIsInvisible) {
        obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
        return true;
    }
    return false;
}

int Custom::setJumpWaitTime() {
    int level = obj().level();
    if (level > 3) {
        level = 3;
    }
    return obj().param().kabu().mJumpWaitTime - level * obj().param().kabu().mJumpWaitTimeStep;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setIsInvisible(bool isInvisible) {
    mIsInvisible = isInvisible;
}

}}}}  // namespace scn::step::enemy::kabu
