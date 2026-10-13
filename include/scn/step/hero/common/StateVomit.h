#ifndef SCN_STEP_HERO_COMMON_STATEVOMIT_H
#define SCN_STEP_HERO_COMMON_STATEVOMIT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateVomit : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateVomit(Hero* hero);
    virtual ~StateVomit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsVomited;
};

}
}
}
}

#endif
