#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEWARPHOLEATTACKNEEDLE_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEWARPHOLEATTACKNEEDLE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateWarpHoleAttackNeedle : public IState {
public:
    StateWarpHoleAttackNeedle(Boss* boss);
    virtual ~StateWarpHoleAttackNeedle();
};

}
}
}
}

#endif
