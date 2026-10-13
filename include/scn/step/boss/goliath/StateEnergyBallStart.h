#ifndef SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateEnergyBallStart : public IState {
public:
    StateEnergyBallStart(Boss* boss, u32 _1, u32 _2, f32 _3);
    virtual ~StateEnergyBallStart();
};

}
}
}
}

#endif
