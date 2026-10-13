#ifndef SCN_STEP_BOSS_COMMON_STATEVACUUMRECEIVE_H
#define SCN_STEP_BOSS_COMMON_STATEVACUUMRECEIVE_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/chara/MoveAlgorithmVacuumReceive.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateVacuumReceive : public StateBase {
public:
    StateVacuumReceive(Boss* boss);
    virtual ~StateVacuumReceive();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    chara::MoveAlgorithmVacuumReceive mMove;
};

}
}
}
}

#endif
