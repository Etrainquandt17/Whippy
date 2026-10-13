#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLTHROW_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLTHROW_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateWallThrow : public IState {
public:
    StateWallThrow(Boss* boss);
    virtual ~StateWallThrow();
};

}
}
}
}

#endif
