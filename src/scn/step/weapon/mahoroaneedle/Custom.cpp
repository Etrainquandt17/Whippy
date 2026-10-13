#include "scn/step/weapon/mahoroaneedle/Custom.h"

#include "app/Random.h"
#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaneedle/StateReady.h"
#include "scn/step/weapon/mahoroaneedle/StateStart.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mUpDir(hel::math::Vector3::BASIS_Y), mRot(0.0f) {}

bool Custom::onInit() {
    obj().mapColl().setValid(false);
    hel::math::Vector3 target = obj().targetPos().toVector3();
    hel::math::Vector3 origin = obj().location().pos();
    hel::math::Vector3 dir = target - origin;
    if (!dir.isZeroLoose(0.00001f)) {
        dir.normalize();
    } else {
        dir = hel::math::Vector3::BASIS_Y;
    }
    mUpDir = dir;
    mRot = 0.017453292f * (360.0f * app::Random::RandNF());
    updateRot(0.0f);
    hel::math::Vector3 pos = obj().location().pos();
    pos.z += 0.75f * app::Random::RandAF();
    obj().location().setPos(pos);
    obj().stateChanger().setNextState<StateReady, Weapon*>(&obj());
    return true;
}

void Custom::reqChangeStateStart() {
    obj().stateChanger().setNextState<StateStart, Weapon*>(&obj());
}

void Custom::updateRot(f32 rot) {
    mRot += rot;
    while (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    while (mRot < 0.0f) {
        mRot += 360.0f;
    }
    hel::math::Direction3 dir;
    dir.mUp = mUpDir;
    dir.restructUpFront();
    dir.mFront.rotate(dir.mUp, 0.017453292f * mRot);
    dir.restructFrontUp();
    obj().model().setCustomMtx(hel::math::Matrix34(dir, hel::math::Vector3::ZERO));
}

hel::math::Vector3 Custom::getUpDir() const {
    return mUpDir;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroaneedle
