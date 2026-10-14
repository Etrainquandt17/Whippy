#include "scn/step/enemy/CustomBase.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {

CustomBase::CustomBase(Enemy& enemy) : mObj(enemy) {}

bool CustomBase::onInit() {
    return false;
}

bool CustomBase::onHitPointIsZero() {
    return false;
}

bool CustomBase::onVacuumReceive() {
    return false;
}

bool CustomBase::onVacuumResist() {
    return false;
}

bool CustomBase::onDamaged() {
    return false;
}

bool CustomBase::onInWater() {
    Enemy* enemy = &mObj;
    enemy->stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(enemy);
    return true;
}

bool CustomBase::onOutWater() {
    return false;
}

bool CustomBase::onRecover() {
    return false;
}

void CustomBase::onCaptured() {}

void CustomBase::onDead() {}

void CustomBase::onProcFixPos() {}

bool CustomBase::reqCustomDeadEffect() {
    return false;
}

void CustomBase::setupSuperEnemyEffect() {}

const RuntimeTypeInfo& CustomBase::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<CustomBase>();
}

Enemy& CustomBase::obj() const {
    return mObj;
}

Enemy& CustomBase::obj() {
    return mObj;
}

}}}  // namespace scn::step::enemy
