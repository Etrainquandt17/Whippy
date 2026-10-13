#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBACKSTEP_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBACKSTEP_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBackStep : public StateBase {
public:
    StateBackStep(Boss* boss);
    virtual ~StateBackStep();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
