#include "scn/step/boss/landia/WaftCtrl.h"

#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/chara/Location.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

WaftCtrl::WaftCtrl(Boss& boss) : mBoss(boss), mRefPos(boss.location().pos()), mTheta(), mThetaVel(), mWidth(), mWidthTarget() {
    mTheta = hel::math::Vector2::ZERO;
    mThetaVel = hel::math::Vector2::ZERO;
    mWidth = hel::math::Vector2::ZERO;
    mWidthTarget = hel::math::Vector2::ZERO;
}

void WaftCtrl::setWaveWidth(const hel::math::Vector2& width) {
    mWidthTarget = width;
}

void WaftCtrl::setWaveWidthZero() {
    mWidthTarget = hel::math::Vector2::ZERO;
}

void WaftCtrl::setWaveThetaVel(const hel::math::Vector2& vel) {
    mThetaVel = vel;
}

void WaftCtrl::setWaveDefault() {
    const Param& param = mBoss.param().landia();
    setWaveWidth(hel::math::Vector2(param.mWaftWidth));
    setWaveThetaVel(hel::math::Vector2(param.mWaftThetaVel, param.mWaftThetaVel));
}

hel::math::Vector3 WaftCtrl::getRefPos() const {
    return mRefPos;
}

void WaftCtrl::setRefPos(const hel::math::Vector3& pos) {
    mRefPos = pos;
}

void WaftCtrl::setPosEnf(const hel::math::Vector3& pos) {
    mWidth = hel::math::Vector2::ZERO;
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
    mWidth = hel::math::Math::LinearInterpolation(mWidth, mWidthTarget, param.mWaftWidthRate);
    hel::math::Vector3 pos(hel::math::Math::SinDegF(mTheta.x) * -mBoss.target().getSign(), hel::math::Math::SinDegF(mTheta.y), 0.0f);
    pos.scale(mWidth.toVector3());
    pos += mRefPos;
    mBoss.location().setPos(pos);
}

}
}
}
}
