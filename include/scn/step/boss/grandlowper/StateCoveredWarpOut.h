#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWARPOUT_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWARPOUT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateCoveredWarpOut : public IState {
public:
    StateCoveredWarpOut(Boss* boss, const hel::math::Vector3& pos);
    virtual ~StateCoveredWarpOut();
};

}

}
}
}

#endif
