#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWARPIN_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWARPIN_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateCoveredWarpIn : public IState {
public:
    StateCoveredWarpIn(Boss* boss);
    virtual ~StateCoveredWarpIn();
};

}

}}}  // namespace scn::step::boss

#endif
