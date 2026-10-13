#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKETATTACK_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKETATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateRocketAttack : public IState {
public:
    StateRocketAttack(Boss* boss, f32 _1, u32 _2, bool _3);
    virtual ~StateRocketAttack();
};

}
}
}
}

#endif
