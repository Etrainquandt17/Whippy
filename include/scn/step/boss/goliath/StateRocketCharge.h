#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKETCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKETCHARGE_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateRocketCharge : public IState {
public:
    StateRocketCharge(Boss* boss);
    virtual ~StateRocketCharge();
};

}
}
}
}

#endif
