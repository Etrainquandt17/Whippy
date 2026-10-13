#ifndef SCN_STEP_BOSS_METALGENERAL_STATERUN_H
#define SCN_STEP_BOSS_METALGENERAL_STATERUN_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateRun : public StateBase {
public:
    StateRun(Boss* boss);
    virtual ~StateRun();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
