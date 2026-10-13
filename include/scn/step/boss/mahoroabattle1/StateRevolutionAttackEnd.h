#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACKEND_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACKEND_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateRevolutionAttackEnd : public IState {
public:
    StateRevolutionAttackEnd(Boss* boss);
    virtual ~StateRevolutionAttackEnd();
};

}
}
}
}

#endif
