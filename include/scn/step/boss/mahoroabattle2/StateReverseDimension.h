#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEREVERSEDIMENSION_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEREVERSEDIMENSION_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateReverseDimension : public IState {
public:
    StateReverseDimension(Boss* boss);
    virtual ~StateReverseDimension();
};

}

}
}
}

#endif
