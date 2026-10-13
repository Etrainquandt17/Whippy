#ifndef SCN_STEP_HERO_COMMON_STATECARRYITEMTHROWFLOAT_H
#define SCN_STEP_HERO_COMMON_STATECARRYITEMTHROWFLOAT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateCarryItemThrowFloat : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCarryItemThrowFloat(Hero* hero);
    virtual ~StateCarryItemThrowFloat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mHoldFrame;
    bool mIsHold;
};

}
}
}
}

#endif
