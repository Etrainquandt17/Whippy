#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHEROSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHEROSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateWallJumpFarHeroStart : public IState {
public:
    StateWallJumpFarHeroStart(Boss* boss, f32 _1, u32 _2);
    virtual ~StateWallJumpFarHeroStart();
};

}
}
}
}

#endif
