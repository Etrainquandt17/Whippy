#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEGLIDEATTACKFAR_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEGLIDEATTACKFAR_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateGlideAttackFar : public IState {
public:
    StateGlideAttackFar(Boss* boss, u32 _1);
    virtual ~StateGlideAttackFar();
};

}

}
}
}

#endif
