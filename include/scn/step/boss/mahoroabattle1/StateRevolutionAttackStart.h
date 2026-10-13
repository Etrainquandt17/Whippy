#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACKSTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACKSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateRevolutionAttackStart : public IState {
public:
    StateRevolutionAttackStart(Boss* boss);
    virtual ~StateRevolutionAttackStart();
};

}
}
}
}

#endif
