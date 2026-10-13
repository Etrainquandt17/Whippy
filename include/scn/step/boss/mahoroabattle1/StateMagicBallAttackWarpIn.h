#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACKWARPIN_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEMAGICBALLATTACKWARPIN_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateMagicBallAttackWarpIn : public IState {
public:
    StateMagicBallAttackWarpIn(Boss* boss);
    virtual ~StateMagicBallAttackWarpIn();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
