#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLELASERSTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPHOLELASERSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateWarpHoleLaserStart : public IState {
public:
    StateWarpHoleLaserStart(Boss* boss, const hel::math::Vector2& pos, u32 _2);
    virtual ~StateWarpHoleLaserStart();
};

}

}}}  // namespace scn::step::boss

#endif
