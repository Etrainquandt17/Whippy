#ifndef SCN_STEP_HERO_COMMON_STATECARRYITEMCATCH_H
#define SCN_STEP_HERO_COMMON_STATECARRYITEMCATCH_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateCarryItemCatch : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCarryItemCatch(Hero* hero);
    virtual ~StateCarryItemCatch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsTrigger0;
    bool mIsTrigger1;
};

}
}
}
}

#endif
