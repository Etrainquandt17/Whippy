#ifndef SCN_STEP_HERO_NEEDLE_STATEATTACK_H
#define SCN_STEP_HERO_NEEDLE_STATEATTACK_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

// TODO: a stand-in until the unit is written.
class StateAttack : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAttack(Hero* hero, bool, bool);
};

}
}
}
}

#endif
