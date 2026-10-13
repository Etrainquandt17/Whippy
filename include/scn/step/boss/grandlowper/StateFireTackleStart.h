#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEFIRETACKLESTART_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEFIRETACKLESTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateFireTackleStart : public IState {
public:
    StateFireTackleStart(Boss* boss, u32 _1, u32 _2);
    virtual ~StateFireTackleStart();
};

}

}
}
}

#endif
