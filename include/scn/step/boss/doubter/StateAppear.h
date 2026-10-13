#ifndef SCN_STEP_BOSS_DOUBTER_STATEAPPEAR_H
#define SCN_STEP_BOSS_DOUBTER_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

// TODO: the members and the overrides (the unit is not written).
class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss);
    virtual ~StateAppear();
};

}
}
}
}

#endif
