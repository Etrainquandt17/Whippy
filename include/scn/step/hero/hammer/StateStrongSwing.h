#ifndef SCN_STEP_HERO_HAMMER_STATESTRONGSWING_H
#define SCN_STEP_HERO_HAMMER_STATESTRONGSWING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateStrongSwing : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateStrongSwing(Hero* hero);
    virtual ~StateStrongSwing();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
