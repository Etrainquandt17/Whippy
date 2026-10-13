#ifndef SCN_STEP_BOSS_LOWPER_STATEFREEZEFALLATTACK_H
#define SCN_STEP_BOSS_LOWPER_STATEFREEZEFALLATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFreezeFallAttack : public StateBase {
public:
    StateFreezeFallAttack(Boss* boss, u32 frame);
    virtual ~StateFreezeFallAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}
}
}
}

#endif
