#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEKILLNEEDLEWARPREADY_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEKILLNEEDLEWARPREADY_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateKillNeedleWarpReady : public IState {
public:
    StateKillNeedleWarpReady(Boss* boss);
    virtual ~StateKillNeedleWarpReady();
};

}

}
}
}

#endif
