#include "scn/step/boss/doubter/WaftPositionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/Location.h"

using hel::math::Math;
using hel::math::Vector3;

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

Vector3 WaftPositionCtrl::getNextPos() const {
    const Param& param = mBoss.param().doubter();
    Vector3 goal = mBoss.location().pos();
    goal.y = param._58 + mBoss.basePos().y;
    goal.y += param._64 * Math::SinDegF(mTheta);
    return Math::LinearInterpolation(mBoss.location().pos(), goal, param._5C);
}

}}}}  // namespace scn::step::boss::doubter
