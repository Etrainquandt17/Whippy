#ifndef SCN_STEP_ENEMY_CAPTURED_STATECAPTUREDBEAM_H
#define SCN_STEP_ENEMY_CAPTURED_STATECAPTUREDBEAM_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace captured {

// TODO: only what the hero's beam states call.
class StateCapturedBeam : public StateBase {
public:
    StateCapturedBeam(Enemy* enemy);
};

}
}
}
}

#endif
