#include "scn/step/boss/landia/WaftCtrl.h"

#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/chara/Location.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace landia {

WaftCtrl::WaftCtrl(Boss& boss) : mBoss(boss), mRefPos(boss.location().pos()), mTheta(), mThetaVel(), mWidth(), mWidthTarget() {
    mTheta = Vector2::ZERO;
    mThetaVel = Vector2::ZERO;
    mWidth = Vector2::ZERO;
    mWidthTarget = Vector2::ZERO;
}

void WaftCtrl::setWaveWidth(const Vector2& width) {
    mWidthTarget = width;
}

void WaftCtrl::setWaveWidthZero() {
    mWidthTarget = Vector2::ZERO;
}

void WaftCtrl::setWaveThetaVel(const Vector2& vel) {
    mThetaVel = vel;
}

void WaftCtrl::setWaveDefault() {
    const Param& param = mBoss.param().landia();
    setWaveWidth(Vector2(param.mWaftWidth));
    setWaveThetaVel(Vector2(param.mWaftThetaVel, param.mWaftThetaVel));
}

Vector3 WaftCtrl::getRefPos() const {
    return mRefPos;
}

void WaftCtrl::setRefPos(const Vector3& pos) {
    mRefPos = pos;
}

void WaftCtrl::setPosEnf(const Vector3& pos) {
    mWidth = Vector2::ZERO;
    mRefPos = pos;
    mBoss.location().setPos(pos);
}

void WaftCtrl::update() {
    const Param& param = mBoss.param().landia();
    mTheta += mThetaVel;
    while (mTheta.x >= 360.0f) {
        mTheta.x -= 360.0f;
    }
    while (mTheta.x < 0.0f) {
        mTheta.x += 360.0f;
    }
    while (mTheta.y >= 360.0f) {
        mTheta.y -= 360.0f;
    }
    while (mTheta.y < 0.0f) {
        mTheta.y += 360.0f;
    }
    mWidth = Math::LinearInterpolation(mWidth, mWidthTarget, param.mWaftWidthRate);
    Vector3 pos(Math::SinDegF(mTheta.x) * -mBoss.target().getSign(), Math::SinDegF(mTheta.y), 0.0f);
    pos.scale(mWidth.toVector3());
    pos += mRefPos;
    mBoss.location().setPos(pos);
}

}}}}  // namespace scn::step::boss::landia
