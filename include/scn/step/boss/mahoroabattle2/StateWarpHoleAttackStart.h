#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLEATTACKSTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLEATTACKSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateWarpHoleAttackStart : public IState {
public:
    StateWarpHoleAttackStart(Boss* boss);
    virtual ~StateWarpHoleAttackStart();
};

}

}}}  // namespace scn::step::boss

#endif
