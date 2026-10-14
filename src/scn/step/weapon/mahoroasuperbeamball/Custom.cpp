#include "scn/step/weapon/mahoroasuperbeamball/Custom.h"

#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroasuperbeamball/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mTargetPos(), mGlideTotalFrame(0), mIsRequestedStartGlide(false) {}

bool Custom::onInit() {
    obj().mapColl().setValid(false);
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

void Custom::reqStartGlide(const Vector3& pos, u32 frame) {
    mTargetPos = pos;
    mGlideTotalFrame = frame;
    mIsRequestedStartGlide = true;
}

Vector3 Custom::getTargetPos() const {
    return mTargetPos;
}

u32 Custom::getGlideTotalFrame() const {
    return mGlideTotalFrame;
}

bool Custom::isRequestedStartGlide() const {
    return mIsRequestedStartGlide;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball
