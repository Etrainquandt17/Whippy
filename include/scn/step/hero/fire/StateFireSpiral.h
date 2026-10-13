#ifndef SCN_STEP_HERO_FIRE_STATEFIRESPIRAL_H
#define SCN_STEP_HERO_FIRE_STATEFIRESPIRAL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class StateFireSpiral : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateFireSpiral(Hero* hero);
    virtual ~StateFireSpiral();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    int mFrame;
    int mLandFrame;
};

}
}
}
}

#endif
