#ifndef SCN_STEP_HERO_COMMON_STATEGUARD_H
#define SCN_STEP_HERO_COMMON_STATEGUARD_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateGuard : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    static bool TryToChangeStateContinue(Hero* hero);

    StateGuard(Hero* hero, bool isStart);
    virtual ~StateGuard();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
