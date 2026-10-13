#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEROLLINGEND_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEROLLINGEND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateRollingEnd : public StateBase {
public:
    StateRollingEnd(Boss* boss);
    virtual ~StateRollingEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
