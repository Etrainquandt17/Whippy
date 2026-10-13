#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEJUMP_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEJUMP_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateJump : public StateBase {
public:
    StateJump(Boss* boss);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
