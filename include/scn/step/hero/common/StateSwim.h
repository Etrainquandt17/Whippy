#ifndef SCN_STEP_HERO_COMMON_STATESWIM_H
#define SCN_STEP_HERO_COMMON_STATESWIM_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

// TODO: the rest of the class, when the unit is written.
class StateSwim : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    StateSwim(Hero* hero);
};

}
}
}
}

#endif
