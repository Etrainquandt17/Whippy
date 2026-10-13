#ifndef SCN_STEP_HERO_GIMMICK_STATEENTERSHIPDOOR_H
#define SCN_STEP_HERO_GIMMICK_STATEENTERSHIPDOOR_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace gimmick {

// TODO: only what the common states call.
class StateEnterShipDoor : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
};

}
}
}
}

#endif
