#include "scn/step/boss/galactaknight/LandCtrl.h"

#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/chara/Location.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

LandCtrl::LandCtrl(Boss& boss) : mBoss(boss), mCenterX(0.0f) {
    mCenterX = boss.basePos().x;
}

f32 LandCtrl::getCenterX() const {
    return mCenterX;
}

f32 LandCtrl::getFloorY() const {
    return mBoss.basePos().y;
}

f32 LandCtrl::getWidth() const {
    const Param& param = mBoss.param().galactaknight();
    return param._4C - param._48;
}

// TODO: two instructions short: the original copies the centre into f1 (fmr f1, f31) ahead of each of the two sums.
f32 LandCtrl::getFarEdgeX(f32 margin) const {
    const Param& param = mBoss.param().galactaknight();
    f32 center = getCenterX();
    if (mBoss.location().pos().x < center) {
        return param._4C + center - margin;
    }
    return margin + (param._48 + center);
}

f32 LandCtrl::getFrontOutSidePosX() const {
    const Param& param = mBoss.param().galactaknight();
    f32 center;
    f32 distance = 0.5f * getWidth() + param._8;
    center = getCenterX();
    return distance * mBoss.target().getSign() + center;
}

bool LandCtrl::isGround() const {
    f32 y = mBoss.location().pos().y;
    return Math::Equals(y, getFloorY(), 0.00001f);
}

}}}}  // namespace scn::step::boss::galactaknight
