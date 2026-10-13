#ifndef SCN_STEP_BOSS_LANDIA_STATEMOVETWINBREATHCONTINUITY_H
#define SCN_STEP_BOSS_LANDIA_STATEMOVETWINBREATHCONTINUITY_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateMoveTwinBreathContinuity : public StateBase {
public:
    struct Config {
        f32 _0;
        hel::math::Vector2 _4;
        bool _C;
    };

    StateMoveTwinBreathContinuity(Boss* boss, Config config);
    virtual ~StateMoveTwinBreathContinuity();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
    Config mConfig;
    bool mIsWaitAnim;
};

}}}}  // namespace scn::step::boss::landia

#endif
