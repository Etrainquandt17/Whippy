#ifndef SCN_STEP_BOSS_WHISPY_STATEROOTATTACK_H
#define SCN_STEP_BOSS_WHISPY_STATEROOTATTACK_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateRootAttack : public StateBase {
public:
    StateRootAttack(Boss* boss);
    virtual ~StateRootAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
