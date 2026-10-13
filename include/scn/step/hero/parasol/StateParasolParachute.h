#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLPARACHUTE_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLPARACHUTE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

// TODO: a stand-in until the unit is written.
class StateParasolParachute : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolParachute(Hero* hero);
};

}
}
}
}

#endif
