#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGREBOUND_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGREBOUND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellRollingRebound : public StateBase {
public:
    StateSwellRollingRebound(Boss* boss);
    virtual ~StateSwellRollingRebound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
