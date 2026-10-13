#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATECALLINGSHOT_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATECALLINGSHOT_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateCallingShot : public IState {
public:
    StateCallingShot(Boss* boss);
    virtual ~StateCallingShot();
};

}

}}}  // namespace scn::step::boss

#endif
