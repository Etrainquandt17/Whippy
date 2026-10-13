#ifndef SCN_STEP_BOSS_LOWPER_STATESPARKATTACK_H
#define SCN_STEP_BOSS_LOWPER_STATESPARKATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSparkAttack : public StateBase {
public:
    StateSparkAttack(Boss* boss, u32 frame);
    virtual ~StateSparkAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsAttack;
    u32 mInterval;
    u32 mIntervalFrame;
};

}}}}  // namespace scn::step::boss::lowper

#endif
