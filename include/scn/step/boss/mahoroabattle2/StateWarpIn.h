#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPIN_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEWARPIN_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateWarpIn : public IState {
public:
    StateWarpIn(Boss* boss);
    virtual ~StateWarpIn();
};

}

}}}  // namespace scn::step::boss

#endif
