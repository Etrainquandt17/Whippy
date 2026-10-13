#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEWARPIN_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEWARPIN_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateWarpIn : public IState {
public:
    StateWarpIn(Boss* boss, bool _1 = false);
    virtual ~StateWarpIn();
};

}

}
}
}

#endif
