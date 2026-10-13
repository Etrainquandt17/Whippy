#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEDEADLYBALLREADY_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEDEADLYBALLREADY_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateDeadlyBallReady : public IState {
public:
    StateDeadlyBallReady(Boss* boss, bool right, u32 _2);
    virtual ~StateDeadlyBallReady();
};

}

}
}
}

#endif
