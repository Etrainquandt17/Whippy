#include "scn/step/boss/doubter/WaftPositionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/Location.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

WaftPositionCtrl::WaftPositionCtrl(Boss& boss) : mBoss(boss), mTheta(0.0f) {}

WaftPositionCtrl::~WaftPositionCtrl() {}

void WaftPositionCtrl::update() {
    const Param& param = mBoss.param().doubter();
    mTheta += param._60;
    if (mTheta >= 360.0f) {
        mTheta -= 360.0f;
    }
}

hel::math::Vector3 WaftPositionCtrl::getNextPos() const {
    const Param& param = mBoss.param().doubter();
    hel::math::Vector3 goal = mBoss.location().pos();
    goal.y = param._58 + mBoss.basePos().y;
    goal.y += param._64 * hel::math::Math::SinDegF(mTheta);
    return hel::math::Math::LinearInterpolation(mBoss.location().pos(), goal, param._5C);
}

}}}}  // namespace scn::step::boss::doubter
