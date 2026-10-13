#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEKILLNEEDLEWARP_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEKILLNEEDLEWARP_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateKillNeedleWarp : public IState {
public:
    StateKillNeedleWarp(Boss* boss);
    virtual ~StateKillNeedleWarp();
};

}

}
}
}

#endif
