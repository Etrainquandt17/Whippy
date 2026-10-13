#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEGLIDEATTACK_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEGLIDEATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateGlideAttack : public IState {
public:
    struct Desc {
        u32 _0;
        f32 _4;
        f32 _8;
        f32 _C;
        f32 _10;
    };

    StateGlideAttack(Boss* boss, const Desc& desc);
    virtual ~StateGlideAttack();
};

}

}
}
}

#endif
