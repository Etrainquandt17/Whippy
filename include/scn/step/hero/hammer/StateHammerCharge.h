#ifndef SCN_STEP_HERO_HAMMER_STATEHAMMERCHARGE_H
#define SCN_STEP_HERO_HAMMER_STATEHAMMERCHARGE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateHammerCharge : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateHammerCharge(Hero* hero);
    virtual ~StateHammerCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsCharged;
    bool mIsEnd;
};

}
}
}
}

#endif
