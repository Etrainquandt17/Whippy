#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEWAVEATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEWAVEATTACK_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateWaveAttack : public IState {
public:
    StateWaveAttack(Boss* boss);
    virtual ~StateWaveAttack();
};

}

}
}
}

#endif
