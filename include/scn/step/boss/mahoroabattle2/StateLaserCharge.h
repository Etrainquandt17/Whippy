#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATELASERCHARGE_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATELASERCHARGE_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateLaserCharge : public IState {
public:
    StateLaserCharge(Boss* boss, const hel::math::Vector2& pos);
    virtual ~StateLaserCharge();
};

}

}}}  // namespace scn::step::boss

#endif
