#ifndef SCN_STEP_BOSS_COMMON_STATEJUMPATTACK_H
#define SCN_STEP_BOSS_COMMON_STATEJUMPATTACK_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateJumpAttackDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateJumpAttack : public StateBase {
public:
    StateJumpAttack(Boss* boss, StateJumpAttackDesc& desc, unsigned long scriptKind);
    virtual ~StateJumpAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsAttack;
    StateJumpAttackDesc& mDesc;
};

}
}
}
}

#endif
