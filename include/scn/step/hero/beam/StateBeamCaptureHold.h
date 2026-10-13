#ifndef SCN_STEP_HERO_BEAM_STATEBEAMCAPTUREHOLD_H
#define SCN_STEP_HERO_BEAM_STATEBEAMCAPTUREHOLD_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

// TODO: only what StateBeamCycleBeam calls.
class StateBeamCaptureHold : public StateBase {
public:
    StateBeamCaptureHold(Hero* hero);
};

}
}
}
}

#endif
