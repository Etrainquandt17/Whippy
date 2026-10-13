#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEENEMYCALL_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEENEMYCALL_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateEnemyCall : public IState {
public:
    StateEnemyCall(Boss* boss, u32 _1);
    virtual ~StateEnemyCall();
};

}
}
}
}

#endif
