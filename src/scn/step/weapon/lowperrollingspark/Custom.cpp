#include "scn/step/weapon/lowperrollingspark/Custom.h"

#include "scn/step/chara/Location.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/lowperrollingspark/StateMain.h"

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

void Custom::setCenterPos(const hel::math::Vector2& pos) {
    mCenterPos = pos;
}

const hel::math::Vector2& Custom::getCenterPos() const {
    return mCenterPos;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
