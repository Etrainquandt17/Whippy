#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACKEND_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACKEND_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateNeedleAttackEnd : public IState {
public:
    StateNeedleAttackEnd(Boss* boss);
    virtual ~StateNeedleAttackEnd();
};

}
}
}
}

#endif
