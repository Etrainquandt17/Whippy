#ifndef SCN_STEP_BOSS_WHISPY_STATEVACUUMEND_H
#define SCN_STEP_BOSS_WHISPY_STATEVACUUMEND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateVacuumEnd : public StateBase {
public:
    StateVacuumEnd(Boss* boss);
    virtual ~StateVacuumEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
