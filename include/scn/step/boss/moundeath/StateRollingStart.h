#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEROLLINGSTART_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEROLLINGSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateRollingStart : public StateBase {
public:
    StateRollingStart(Boss* boss);
    virtual ~StateRollingStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mRot;
    f32 mRotDiff;
};

}
}
}
}

#endif
