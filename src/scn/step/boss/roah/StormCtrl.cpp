#include "scn/step/boss/roah/StormCtrl.h"

#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Param.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StormCtrl::StormCtrl(Boss& boss) : mBoss(boss), mIsValid(false), mCount(0), mTime(0) {}

void StormCtrl::update() {
    if (mIsValid) {
        mCount++;
    }
}

void StormCtrl::toValid(u32 time) {
    mIsValid = true;
    mCount = 0;
    mTime = time;
}

void StormCtrl::toInvalid() {
    mIsValid = false;
}

bool StormCtrl::isDamageTiming() const {
    const Param& param = mBoss.param().roah();
    if (!mIsValid) {
        return false;
    }
    f32 rate = static_cast<f32>(mTime) / static_cast<f32>(param.mStormDamageTime);
    rate = hel::math::Math::Max(1.0f, rate);
    if (mCount % static_cast<u32>(rate) == 0) {
        return mCount != mTime;
    }
    return false;
}

}
}
}
}
