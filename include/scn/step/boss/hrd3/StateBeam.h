#ifndef SCN_STEP_BOSS_HRD3_STATEBEAM_H
#define SCN_STEP_BOSS_HRD3_STATEBEAM_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace hrd3 {

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
