#ifndef SCN_STEP_BOSS_GOLIATH_STATESWOOPRISE_H
#define SCN_STEP_BOSS_GOLIATH_STATESWOOPRISE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateSwoopRise : public StateBase {
public:
    StateSwoopRise(Boss* boss, u32 time, u32 waitTime);
    virtual ~StateSwoopRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mTime;
    u32 mWaitFrame;
    u32 mWaitTime;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mShakeWait;
};

}}}}  // namespace scn::step::boss::goliath

#endif
