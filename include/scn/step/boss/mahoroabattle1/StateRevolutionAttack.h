#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEREVOLUTIONATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateRevolutionAttack : public IState {
public:
    StateRevolutionAttack(Boss* boss, const hel::math::Vector2& pos);
    virtual ~StateRevolutionAttack();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
