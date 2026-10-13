#include "scn/step/weapon/rollexp/Custom.h"

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace rollexp {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mAttackType(static_cast<ocoll::AttackType>(0x241)), mAttackRadius(1.0f), mAttackFrame(5) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::changeAttackType(ocoll::AttackType type) {
    mAttackType = type;
}

ocoll::AttackType Custom::getAttackType() const {
    return mAttackType;
}

void Custom::setAttackRadius(f32 radius) {
    mAttackRadius = radius;
}

f32 Custom::getAttackRadius() const {
    return mAttackRadius;
}

void Custom::setAttackFrame(u32 frame) {
    mAttackFrame = frame;
}

u32 Custom::getAttackFrame() const {
    return mAttackFrame;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::rollexp
