#ifndef SCN_STEP_HERO_STONE_STATEUPPER_H
#define SCN_STEP_HERO_STONE_STATEUPPER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class StateUpper : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateUpper(Hero* hero);
    virtual ~StateUpper();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
