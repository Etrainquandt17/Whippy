#include "scn/step/boss/roah/RotCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "util/ObjList.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

RotCtrl::RotCtrl(Boss& boss)
    : mBoss(boss), mRotX(0.0f), mRotXMax(0.0f), mFixRotRate(0.0f), mRotY(0.0f), mRotYMax(0.0f), mIsValid(true),
      mLocalMtxTempRot(Vector3::ZERO) {
    const Param& param = mBoss.param().roah();
    mRotXMax = param.mRotXMax;
    mRotYMax = param.mRotYMax;
    mFixRotRate = param.mFixRotRate;
    mBoss.model().rotCtrl().setValid(false);
}

void RotCtrl::update() {
    const Param& param = mBoss.param().roah();
    if (!mIsValid) {
        mRotX = 0.0f;
        mRotY = param.mRotYMax * mBoss.target().getSign();
        return;
    }
    f32 diff = mBoss.location().pos().y - mBoss.location().prevPos().y;
    if (Math::Abs(diff) > param.mRotMoveMargin) {
        f32 target = diff > 0.0f ? -mRotXMax : mRotXMax;
        mRotX = Math::LinearInterpolation(mRotX, target, mFixRotRate);
    } else {
        mRotX = Math::LinearInterpolation(mRotX, 0.0f, mFixRotRate);
    }
    f32 targetY = mRotYMax * mBoss.target().getSign();
    mRotY = Math::LinearInterpolation(mRotY, targetY, mFixRotRate);
    NodeAccessor node = mBoss.model().model().nodes().at(1);
    Matrix34 mtx = Matrix34::CreateRotXYZDeg(Vector3(mRotX, 0.0f, 0.0f)) *
                   Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRotY, 0.0f));
    node.localMtx().setRTMtx(mtx);
}

void RotCtrl::toValid() {
    mIsValid = true;
    mBoss.model().model().nodes().at(1).localMtx().reset();
}

void RotCtrl::toInvalid() {
    mIsValid = false;
    mBoss.model().model().nodes().at(1).localMtx().reset();
}

void RotCtrl::setRotXMax(f32 rot) {
    mRotXMax = rot;
}

void RotCtrl::setRotYMax(f32 rot) {
    mRotYMax = rot;
}

void RotCtrl::setFixRotRate(f32 rate) {
    mFixRotRate = rate;
}

f32 RotCtrl::getRotX() {
    return mRotX;
}

f32 RotCtrl::getRotY() {
    return mRotY;
}

void RotCtrl::setLocalMtxTempRot(f32 x, f32 y, f32 z) {
    while (x < -180.0f) {
        x += 360.0f;
    }
    while (x > 180.0f) {
        x -= 360.0f;
    }
    while (y < -180.0f) {
        y += 360.0f;
    }
    while (y > 180.0f) {
        y -= 360.0f;
    }
    while (z < -180.0f) {
        z += 360.0f;
    }
    while (z > 180.0f) {
        z -= 360.0f;
    }
    mLocalMtxTempRot.set(x, y, z);
}

Vector3 RotCtrl::getLocalMtxTempRot() {
    return mLocalMtxTempRot;
}

void RotCtrl::resetLocalMtxTempRot() {
    mLocalMtxTempRot = Vector3::ZERO;
}

}}}}  // namespace scn::step::boss::roah
