#include "scn/step/boss/InfoHitPointCtrl.h"

#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/HitPoint.h"

namespace scn {
namespace step {
namespace boss {

InfoHitPointCtrl::InfoHitPointCtrl(Boss& boss) : mBoss(boss), mZero(0), mFull(0) {}

InfoHitPointCtrl::~InfoHitPointCtrl() {}

f32 InfoHitPointCtrl::getHitPointRate() const {
    if (mZero == 0 && mFull == 0) {
        return mBoss.hitPoint().rate();
    }
    u32 full = mFull != 0 ? mFull : mBoss.hitPoint().getMax();
    u32 zero = mZero;
    f32 rate = (static_cast<f32>(mBoss.hitPoint().get()) - static_cast<f32>(zero)) / static_cast<f32>(full - zero);
    return hel::math::Math::LimitMinMax(rate, 0.0f, 1.0f);
}

// TODO: the link dropped this function; the body is a guess of the right size.
bool InfoHitPointCtrl::isInfoHitPointZero() const {
    return mBoss.hitPoint().get() <= mZero;
}

void InfoHitPointCtrl::setZero(u32 value) {
    if (value <= mBoss.hitPoint().getMax() && (mFull == 0 || value <= mFull)) {
        mZero = value;
    }
}

void InfoHitPointCtrl::unsetZero() {
    mZero = 0;
}

void InfoHitPointCtrl::setFull(u32 value) {
    if (value < mZero) {
        return;
    }
    mFull = value;
}

void InfoHitPointCtrl::unsetFull() {
    mFull = 0;
}

}
}
}
