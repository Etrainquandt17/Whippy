#ifndef SCN_STEP_BOSS_METALGENERAL_STATECENTERJUMP_H
#define SCN_STEP_BOSS_METALGENERAL_STATECENTERJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateCenterJump : public StateBase {
public:
    StateCenterJump(Boss* boss);
    virtual ~StateCenterJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}
}
}
}

#endif
