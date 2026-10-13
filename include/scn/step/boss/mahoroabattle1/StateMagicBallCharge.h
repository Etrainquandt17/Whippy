#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLCHARGE_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLCHARGE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateMagicBallCharge : public IState {
public:
    StateMagicBallCharge(Boss* boss);
    virtual ~StateMagicBallCharge();
};

}
}
}
}

#endif
