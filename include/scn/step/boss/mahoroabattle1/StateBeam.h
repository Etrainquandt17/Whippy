#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEBEAM_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEBEAM_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateBeam : public IState {
public:
    StateBeam(Boss* boss);
    virtual ~StateBeam();
};

}
}
}
}

#endif
