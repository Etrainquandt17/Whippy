#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEMENACE_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEMENACE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateMenace : public IState {
public:
    StateMenace(Boss* boss, bool moveCenter);
    virtual ~StateMenace();
};

}

}
}
}

#endif
