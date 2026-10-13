#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateMagicBallAttack : public IState {
public:
    StateMagicBallAttack(Boss* boss);
    virtual ~StateMagicBallAttack();
};

}
}
}
}

#endif
