#include "scn/step/boss/whispy/StateShotAirBallBase.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateShotAirBallBase::StateShotAirBallBase(Boss* boss, u32 count, u32 intervalFirst, u32 interval)
    : StateBase(boss), mIsFirst(true), _C(0), mCount(count), mIntervalFirst(intervalFirst), mInterval(interval), mTimer(0), mIsWait(false) {
    obj().model().reqScript(6);
}

void StateShotAirBallBase::procAnim() {
    if (obj().model().isAllEnd()) {
        if (mCount == 0) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
        obj().model().reqScript(7);
        mTimer = mIsFirst ? mIntervalFirst : mInterval;
        mIsWait = true;
        mIsFirst = false;
    }
    if (mIsWait) {
        if (mTimer != 0) {
            mTimer--;
        } else {
            if (mCount > 1) {
                obj().model().reqScript(8);
            } else {
                obj().model().reqScript(9);
            }
            reqAirBall();
            mIsWait = false;
            mCount--;
        }
    }
}

void StateShotAirBallBase::procMove() {}

void StateShotAirBallBase::procFixPos() {}

}
}
}
}
