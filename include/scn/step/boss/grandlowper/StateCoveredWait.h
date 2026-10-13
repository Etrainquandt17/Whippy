#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWAIT_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATECOVEREDWAIT_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateCoveredWait : public IState {
public:
    StateCoveredWait(Boss* boss);
    virtual ~StateCoveredWait();
};

}

}}}  // namespace scn::step::boss

#endif
