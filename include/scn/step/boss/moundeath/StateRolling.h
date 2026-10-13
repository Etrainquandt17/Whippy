#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEROLLING_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEROLLING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateRolling : public StateBase {
public:
    StateRolling(Boss* boss);
    virtual ~StateRolling();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mRot;
    u32 mWait;
    bool mIsRight;
};

}
}
}
}

#endif
