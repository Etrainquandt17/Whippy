#ifndef SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKHOLD_H
#define SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKHOLD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFreezeAttackHold : public StateBase {
public:
    StateFreezeAttackHold(Boss* boss, u32 frame);
    virtual ~StateFreezeAttackHold();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    u32 mShakeWait;
};

}
}
}
}

#endif
