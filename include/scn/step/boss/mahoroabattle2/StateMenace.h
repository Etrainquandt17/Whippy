#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEMENACE_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEMENACE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateMenace : public IState {
public:
    StateMenace(Boss* boss);
    virtual ~StateMenace();
};

}

}}}  // namespace scn::step::boss

#endif
