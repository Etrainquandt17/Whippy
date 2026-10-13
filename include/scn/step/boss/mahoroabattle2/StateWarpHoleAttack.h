#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLEATTACK_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLEATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateWarpHoleAttack : public IState {
public:
    StateWarpHoleAttack(Boss* boss, const hel::math::Vector3& _1, const hel::math::Vector3& _2, u32 _3);
    virtual ~StateWarpHoleAttack();
};

}

}}}  // namespace scn::step::boss

#endif
