#include "scn/step/enemy/mumbies/Custom.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/mumbies/StateEndure.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mEndureFlag(false), mIsDead(false) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

bool Custom::onVacuumResist() {
    if (!mEndureFlag && !mIsDead) {
        obj().stateChanger().setNextState<StateEndure, Enemy*>(&obj());
        mEndureFlag = true;
    }
    return true;
}

bool Custom::onInWater() {
    obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
    return false;
}

bool Custom::onHitPointIsZero() {
    mIsDead = true;
    return false;
}

bool Custom::onDamaged() {
    mIsDead = true;
    return false;
}

void Custom::onCaptured() {
    mIsDead = true;
}

bool Custom::onRecover() {
    mIsDead = false;
    return false;
}

void Custom::setEndureFlag(bool endureFlag) {
    mEndureFlag = endureFlag;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::mumbies
