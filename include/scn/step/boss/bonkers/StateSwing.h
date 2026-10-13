#ifndef SCN_STEP_BOSS_BONKERS_STATESWING_H
#define SCN_STEP_BOSS_BONKERS_STATESWING_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/bonkers/StateJumpBigStart.h"
#include "scn/step/boss/bonkers/StateSwingPursuit.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateSwing : public StateBase {
public:
    StateSwing(Boss* boss);
    virtual ~StateSwing();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsMove;
    u32 mCount;
};

}
}
}
}

#endif
