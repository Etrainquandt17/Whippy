#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateNeedleAttack : public IState {
public:
    StateNeedleAttack(Boss* boss, u32 _1, int kind);
    virtual ~StateNeedleAttack();
};

}
}
}
}

#endif
