#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDIVE_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDIVE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

// TODO: a stand-in until the unit is written.
class StateParasolWaterDive : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolWaterDive(Hero* hero);
};

}
}
}
}

#endif
