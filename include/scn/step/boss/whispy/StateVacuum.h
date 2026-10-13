#ifndef SCN_STEP_BOSS_WHISPY_STATEVACUUM_H
#define SCN_STEP_BOSS_WHISPY_STATEVACUUM_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateVacuum : public StateBase {
public:
    StateVacuum(Boss* boss);
    virtual ~StateVacuum();
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();

private:
    u32 mCount;
    u32 mEnemyTimer;
};

}
}
}
}

#endif
