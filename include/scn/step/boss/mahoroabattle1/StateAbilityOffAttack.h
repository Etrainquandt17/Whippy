#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEABILITYOFFATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEABILITYOFFATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateAbilityOffAttack : public IState {
public:
    StateAbilityOffAttack(Boss* boss);
    virtual ~StateAbilityOffAttack();
};

}
}
}
}

#endif
