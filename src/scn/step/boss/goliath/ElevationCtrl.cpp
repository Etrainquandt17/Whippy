#include "scn/step/boss/goliath/ElevationCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

const f32 T_ELEV_MIN = -5.0f;
const f32 T_ELEV_MAX = 60.0f;

}

ElevationCtrl::ElevationCtrl(Boss& boss)
    : mBoss(boss), mElevX(0.0f), mTargetElevX(0.0f), mElevZ(0.0f), mTargetElevZ(0.0f), mIntpRateX(0.5f), mIntpRateZ(0.5f) {}

void ElevationCtrl::update() {
    mElevX = Math::LinearInterpolation(mElevX, mTargetElevX, mIntpRateX);
    mElevZ = Math::LinearInterpolation(mElevZ, mTargetElevZ, mIntpRateZ);
    NodeAccessor node = mBoss.model().model().nodes().at(3);
    node.localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(-mElevX, 0.0f, mElevZ * mBoss.target().getSign())));
}

void ElevationCtrl::setElevX(f32 elev) {
    mTargetElevX = Math::LimitMinMax(elev, T_ELEV_MIN, T_ELEV_MAX);
}

void ElevationCtrl::setElevZ(f32 elev) {
    mTargetElevZ = Math::LimitMinMax(elev, T_ELEV_MIN, T_ELEV_MAX);
}

void ElevationCtrl::resetElev() {
    setElevX(0.0f);
    setElevZ(0.0f);
}

void ElevationCtrl::setIntpRateX(f32 rate) {
    mIntpRateX = rate;
}

void ElevationCtrl::setIntpRateZ(f32 rate) {
    mIntpRateZ = rate;
}

void ElevationCtrl::resetIntpRate() {
    mIntpRateX = 0.5f;
    mIntpRateZ = 0.5f;
}

f32 ElevationCtrl::getElevX() const {
    return mElevX;
}

f32 ElevationCtrl::getElevZ() const {
    return mElevZ;
}

}}}}  // namespace scn::step::boss::goliath
