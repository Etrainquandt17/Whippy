#ifndef SCN_STEP_HERO_LEAF_STATESHOT_H
#define SCN_STEP_HERO_LEAF_STATESHOT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateShot : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateShot(Hero* hero);
    virtual ~StateShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mWait;
    u32 mShotCount;
};

}
}
}
}

#endif
