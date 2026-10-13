#ifndef SCN_STEP_HERO_WING_STATESHUTTLELOOPEND_H
#define SCN_STEP_HERO_WING_STATESHUTTLELOOPEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

class StateShuttleLoopEnd : public StateBase {
public:
    StateShuttleLoopEnd(Hero* hero);
    virtual ~StateShuttleLoopEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
