#ifndef SCN_STEP_HERO_HAMMER_STATESTRONGAIRSPIN_H
#define SCN_STEP_HERO_HAMMER_STATESTRONGAIRSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateStrongAirSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateStrongAirSpin(Hero* hero);
    virtual ~StateStrongAirSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsEnd;
};

}
}
}
}

#endif
