#ifndef SCN_STEP_HERO_COMMON_STATERUN_H
#define SCN_STEP_HERO_COMMON_STATERUN_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateRun : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateRun(Hero* hero);
    virtual ~StateRun();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsVacuum;
};

}
}
}
}

#endif
