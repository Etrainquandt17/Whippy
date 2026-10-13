#ifndef SCN_STEP_BOSS_GOLIATH_STATEGROUNDPUNCH_H
#define SCN_STEP_BOSS_GOLIATH_STATEGROUNDPUNCH_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateGroundPunch : public IState {
public:
    StateGroundPunch(Boss* boss);
    virtual ~StateGroundPunch();
};

}
}
}
}

#endif
