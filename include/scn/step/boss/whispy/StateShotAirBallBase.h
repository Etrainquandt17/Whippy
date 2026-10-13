#ifndef SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLBASE_H
#define SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLBASE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateShotAirBallBase : public StateBase {
public:
    StateShotAirBallBase(Boss* boss, u32 count, u32 intervalFirst, u32 interval);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void reqAirBall() = 0;

private:
    bool mIsFirst;
    u32 _C;
    u32 mCount;
    u32 mIntervalFirst;
    u32 mInterval;
    u32 mTimer;
    bool mIsWait;
};

}}}}  // namespace scn::step::boss::whispy

#endif
