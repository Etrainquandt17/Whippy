#ifndef SCN_STEP_HERO_TORNADO_STATECHARGEATTACK_H
#define SCN_STEP_HERO_TORNADO_STATECHARGEATTACK_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

class StateChargeAttack : public StateBase {
public:
    StateChargeAttack(Hero* hero);
    virtual ~StateChargeAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsStart;
    bool mIsEnd;
};

}
}
}
}

#endif
