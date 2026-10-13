#ifndef SCN_STEP_HERO_COMMON_STATESQUASHROOF_H
#define SCN_STEP_HERO_COMMON_STATESQUASHROOF_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSquashRoof : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSquashRoof(Hero* hero);
    virtual ~StateSquashRoof();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
