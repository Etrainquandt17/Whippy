#ifndef SCN_STEP_BOSS_COMMON_STATEATTACK_H
#define SCN_STEP_BOSS_COMMON_STATEATTACK_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateAttackDesc.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class StateAttack : public StateBase {
public:
    StateAttack(Boss* boss, StateAttackDesc& desc, unsigned long scriptKind);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateAttackDesc& mDesc;
};

}
}
}
}

#endif
