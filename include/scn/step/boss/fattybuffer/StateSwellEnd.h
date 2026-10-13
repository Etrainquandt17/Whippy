#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLEND_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLEND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellEnd : public StateBase {
public:
    StateSwellEnd(Boss* boss);
    virtual ~StateSwellEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
