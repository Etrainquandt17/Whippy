#ifndef SCN_STEP_HERO_COMMON_STATECHANGEABILITYENF_H
#define SCN_STEP_HERO_COMMON_STATECHANGEABILITYENF_H

#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateChangeAbilityEnf : public StateBase {
public:
    StateChangeAbilityEnf(Hero* hero, AbilityKind kind);
    virtual ~StateChangeAbilityEnf();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    AbilityKind mKind;
};

}
}
}
}

#endif
