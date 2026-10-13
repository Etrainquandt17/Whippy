#ifndef SCN_STEP_HERO_HAMMER_STATEHAMMERATTACK_H
#define SCN_STEP_HERO_HAMMER_STATEHAMMERATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateHammerAttack : public StateBase {
public:
    StateHammerAttack(Hero* hero);
    virtual ~StateHammerAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsSwing;
};

}
}
}
}

#endif
