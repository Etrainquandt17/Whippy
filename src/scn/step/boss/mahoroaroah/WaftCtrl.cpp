#include "scn/step/boss/mahoroaroah/WaftCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/mahoroaroah/Param.h"
#include "scn/step/chara/Location.h"

using hel::math::Math;
using hel::math::Vec3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

namespace {

const Vec3 T_DEFAULT_THETAVEL = { 1.1f, 1.7f, 0.6f };

}

WaftCtrl::WaftCtrl(Boss& boss)
    : mBoss(boss), mRefPos(boss.location().pos()), mTheta(Vector3::ZERO), mThetaVel(T_DEFAULT_THETAVEL), mIsValid(false) {}

WaftCtrl::~WaftCtrl() {}

Vector3 WaftCtrl::getRefPos() const {
    return mRefPos;
}

void WaftCtrl::setRefPos(const Vector3& pos) {
    mRefPos = pos;
}

void WaftCtrl::update() {
    const Param& param = mBoss.param().mahoroaroah();
    if (mIsValid) {
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
        while (mTheta.z >= 360.0f) {
            mTheta.z -= 360.0f;
        }
        while (mTheta.z < 0.0f) {
            mTheta.z += 360.0f;
        }
        Vector3 pos(Math::SinDegF(mTheta.x), Math::SinDegF(mTheta.y), Math::SinDegF(mTheta.z));
        pos.scale(Vector3(param.mWaftWidth));
        pos += mRefPos;
        mBoss.location().setPos(pos);
    }
}

void WaftCtrl::setToValid() {
    mIsValid = true;
}

}}}}  // namespace scn::step::boss::mahoroaroah
