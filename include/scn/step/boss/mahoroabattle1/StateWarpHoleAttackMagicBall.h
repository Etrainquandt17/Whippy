#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEWARPHOLEATTACKMAGICBALL_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEWARPHOLEATTACKMAGICBALL_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateWarpHoleAttackMagicBall : public IState {
public:
    StateWarpHoleAttackMagicBall(Boss* boss);
    virtual ~StateWarpHoleAttackMagicBall();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
