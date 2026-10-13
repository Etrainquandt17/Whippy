#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLCLIMB_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLCLIMB_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateWallClimb : public IState {
public:
    StateWallClimb(Boss* boss, f32 _1, u32 _2);
    virtual ~StateWallClimb();
};

}
}
}
}

#endif
