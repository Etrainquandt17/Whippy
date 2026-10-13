#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLSWING_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLSWING_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

// TODO: a stand-in until the unit is written.
class StateParasolSwing : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolSwing(Hero* hero);
};

}
}
}
}

#endif
