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

namespace scn {
namespace step {
namespace boss {
namespace roah {

RotCtrl::RotCtrl(Boss& boss)
    : mBoss(boss), mRotX(0.0f), mRotXMax(0.0f), mFixRotRate(0.0f), mRotY(0.0f), mRotYMax(0.0f), mIsValid(true),
      mLocalMtxTempRot(hel::math::Vector3::ZERO) {
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
    if (hel::math::Math::Abs(diff) > param.mRotMoveMargin) {
        f32 target = diff > 0.0f ? -mRotXMax : mRotXMax;
        mRotX = hel::math::Math::LinearInterpolation(mRotX, target, mFixRotRate);
    } else {
        mRotX = hel::math::Math::LinearInterpolation(mRotX, 0.0f, mFixRotRate);
    }
    f32 targetY = mRotYMax * mBoss.target().getSign();
    mRotY = hel::math::Math::LinearInterpolation(mRotY, targetY, mFixRotRate);
    g3d::NodeAccessor node = mBoss.model().model().nodes().at(1);
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(mRotX, 0.0f, 0.0f)) *
                              hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, mRotY, 0.0f));
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

hel::math::Vector3 RotCtrl::getLocalMtxTempRot() {
    return mLocalMtxTempRot;
}

void RotCtrl::resetLocalMtxTempRot() {
    mLocalMtxTempRot = hel::math::Vector3::ZERO;
}

}}}}  // namespace scn::step::boss::roah
