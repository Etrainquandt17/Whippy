#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACKWARPOUT_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACKWARPOUT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateMagicBallAttackWarpOut : public IState {
public:
    StateMagicBallAttackWarpOut(Boss* boss, const hel::math::Vector3& pos);
    virtual ~StateMagicBallAttackWarpOut();
};

}
}
}
}

#endif
