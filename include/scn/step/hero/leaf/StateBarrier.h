#ifndef SCN_STEP_HERO_LEAF_STATEBARRIER_H
#define SCN_STEP_HERO_LEAF_STATEBARRIER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateBarrier : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateBarrier(Hero* hero);
    virtual ~StateBarrier();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsEnd;
};

}
}
}
}

#endif
