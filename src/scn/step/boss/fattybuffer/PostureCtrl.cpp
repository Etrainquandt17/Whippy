#include "scn/step/boss/fattybuffer/PostureCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
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
namespace fattybuffer {

PostureCtrl::PostureCtrl(Boss& boss) : mBoss(boss), mAngle(0.0f), mTargetAngle(0.0f), mRate(0.1f) {}

void PostureCtrl::update() {
    if (!Math::Equals(mAngle, mTargetAngle, 0.00001f)) {
        mAngle = Math::Interpolate(mAngle, mTargetAngle, mRate);
        NodeAccessor node = mBoss.model().model().nodes().at(3);
        node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mAngle)));
    }
}

void PostureCtrl::resetTarget() {
    mTargetAngle = 0.0f;
    mRate = 0.1f;
}

void PostureCtrl::setTargetRoof() {
    mTargetAngle = 180.0f;
    mRate = 0.2f;
}

f32 PostureCtrl::getUpSign() const {
    return mAngle < 90.0f ? 1.0f : -1.0f;
}

}}}}  // namespace scn::step::boss::fattybuffer
