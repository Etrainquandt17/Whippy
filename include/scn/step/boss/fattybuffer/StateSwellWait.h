#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLWAIT_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLWAIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellWait : public StateBase {
public:
    StateSwellWait(Boss* boss);
    virtual ~StateSwellWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
