#include "scn/step/boss/hrd3/LandCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

LandCtrl::LandCtrl(Boss& boss) : mBoss(boss), mCenterX(0.0f) {
    mCenterX = boss.basePos().x - 5.0f;
}

f32 LandCtrl::getCenterX() const {
    return mCenterX;
}

f32 LandCtrl::getWidth() const {
    return 22.0f;
}

f32 LandCtrl::getFloorY() const {
    return mBoss.basePos().y;
}

f32 LandCtrl::getAdjustX(f32 x, f32 margin) const {
    return getAdjustX(x, margin, margin, true);
}

// TODO: one instruction differs: the original adds the centre and the half width as fadds f0, f5, f3; this gives
// the operands the other way round, whichever way the sum is written. A named half width swaps two registers.
f32 LandCtrl::getAdjustX(f32 x, f32 left, f32 right, bool isRight) const {
    f32 minMargin = isRight ? right : left;
    f32 maxMargin = isRight ? left : right;
    f32 center = mCenterX;
    f32 min = minMargin + (center - 11.0f);
    f32 max = center + 11.0f - maxMargin;
    if (max <= min) {
        return center;
    }
    return hel::math::Math::LimitMinMax(x, min, max);
}

}
}
}
}
