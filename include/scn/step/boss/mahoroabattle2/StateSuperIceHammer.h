#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERICEHAMMER_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERICEHAMMER_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateSuperIceHammer : public IState {
public:
    StateSuperIceHammer(Boss* boss, const hel::math::Vector3& pos);
    virtual ~StateSuperIceHammer();
};

}

}}}  // namespace scn::step::boss

#endif
