#ifndef SCN_STEP_BOSS_WHISPY_STATEVACUUMSTART_H
#define SCN_STEP_BOSS_WHISPY_STATEVACUUMSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateVacuumStart : public StateBase {
public:
    StateVacuumStart(Boss* boss);
    virtual ~StateVacuumStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
