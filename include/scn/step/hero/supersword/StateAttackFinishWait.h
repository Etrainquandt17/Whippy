#ifndef SCN_STEP_HERO_SUPERSWORD_STATEATTACKFINISHWAIT_H
#define SCN_STEP_HERO_SUPERSWORD_STATEATTACKFINISHWAIT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

class StateAttackFinishWait : public StateBase {
public:
    StateAttackFinishWait(Hero* hero);
    virtual ~StateAttackFinishWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();
};

}
}
}
}

#endif
