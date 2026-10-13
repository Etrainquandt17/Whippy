#ifndef SCN_STEP_HERO_BEAM_STATEBEAMCHARGE_H
#define SCN_STEP_HERO_BEAM_STATEBEAMCHARGE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

// TODO: only what the ability class calls.
class StateBeamCharge : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateBeamCharge(Hero* hero);
};

}
}
}
}

#endif
