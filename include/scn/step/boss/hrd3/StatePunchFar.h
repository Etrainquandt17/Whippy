#ifndef SCN_STEP_BOSS_HRD3_STATEPUNCHFAR_H
#define SCN_STEP_BOSS_HRD3_STATEPUNCHFAR_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace hrd3 {

// TODO: members.
class StatePunchFar : public IState {
public:
    StatePunchFar(Boss* boss);
    virtual ~StatePunchFar();
};

}
}
}
}

#endif
