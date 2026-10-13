#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGLANDING_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLROLLINGLANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellRollingLanding : public StateBase {
public:
    StateSwellRollingLanding(Boss* boss);
    virtual ~StateSwellRollingLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
