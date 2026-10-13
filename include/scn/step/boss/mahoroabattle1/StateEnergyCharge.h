#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEENERGYCHARGE_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEENERGYCHARGE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateEnergyCharge : public IState {
public:
    StateEnergyCharge(Boss* boss);
    virtual ~StateEnergyCharge();
};

}
}
}
}

#endif
