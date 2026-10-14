#include "scn/step/weapon/lowperrollingspark/Custom.h"

#include "scn/step/chara/Location.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/lowperrollingspark/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace lowperrollingspark {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mTotalFrame(1), mDelayFrame(0), mRotAngle(0.0f), mCenterPos(weapon.location().pos().getXY()) {}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::setTotalFrame(u32 frame) {
    mTotalFrame = frame;
}

u32 Custom::getTotalFrame() const {
    return mTotalFrame;
}

void Custom::setDelayFrame(u32 frame) {
    mDelayFrame = frame;
}

u32 Custom::getDelayFrame() const {
    return mDelayFrame;
}

void Custom::setRotAngle(f32 angle) {
    mRotAngle = angle;
}

f32 Custom::getRotAngle() const {
    return mRotAngle;
}

void Custom::setCenterPos(const Vector2& pos) {
    mCenterPos = pos;
}

const Vector2& Custom::getCenterPos() const {
    return mCenterPos;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::lowperrollingspark
