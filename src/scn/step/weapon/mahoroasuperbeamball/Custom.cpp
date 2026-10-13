#include "scn/step/weapon/mahoroasuperbeamball/Custom.h"

#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroasuperbeamball/StateMain.h"

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

void Custom::reqStartGlide(const hel::math::Vector3& pos, u32 frame) {
    mTargetPos = pos;
    mGlideTotalFrame = frame;
    mIsRequestedStartGlide = true;
}

hel::math::Vector3 Custom::getTargetPos() const {
    return mTargetPos;
}

u32 Custom::getGlideTotalFrame() const {
    return mGlideTotalFrame;
}

bool Custom::isRequestedStartGlide() const {
    return mIsRequestedStartGlide;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball
