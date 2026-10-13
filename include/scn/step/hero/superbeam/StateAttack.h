#ifndef SCN_STEP_HERO_SUPERBEAM_STATEATTACK_H
#define SCN_STEP_HERO_SUPERBEAM_STATEATTACK_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace superbeam {

// TODO: a stand-in until the unit is written.
class StateAttack : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAttack(Hero* hero);
};

}
}
}
}

#endif
