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

using app::Random;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Direction3;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

Custom::Custom(Weapon& weapon) : CustomBase(weapon), mUpDir(Vector3::BASIS_Y), mRot(0.0f) {}

bool Custom::onInit() {
    obj().mapColl().setValid(false);
    Vector3 target = obj().targetPos().toVector3();
    Vector3 origin = obj().location().pos();
    Vector3 dir = target - origin;
    if (!dir.isZeroLoose(0.00001f)) {
        dir.normalize();
    } else {
        dir = Vector3::BASIS_Y;
    }
    mUpDir = dir;
    mRot = 0.017453292f * (360.0f * Random::RandNF());
    updateRot(0.0f);
    Vector3 pos = obj().location().pos();
    pos.z += 0.75f * Random::RandAF();
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
    Direction3 dir;
    dir.mUp = mUpDir;
    dir.restructUpFront();
    dir.mFront.rotate(dir.mUp, 0.017453292f * mRot);
    dir.restructFrontUp();
    obj().model().setCustomMtx(Matrix34(dir, Vector3::ZERO));
}

Vector3 Custom::getUpDir() const {
    return mUpDir;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroaneedle
