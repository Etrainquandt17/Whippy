#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTCLIMB_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTCLIMB_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StatePatriotClimb : public StateBase {
public:
    StatePatriotClimb(Boss* boss);
    virtual ~StatePatriotClimb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsSignaled;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}
}
}
}

#endif
