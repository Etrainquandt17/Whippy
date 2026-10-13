#ifndef SCN_STEP_HERO_INTERFERENCE_STATESPACEJUMP_H
#define SCN_STEP_HERO_INTERFERENCE_STATESPACEJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace interference {

// TODO: only what the common states call.
class StateSpaceJump : public StateBase {
public:
    // TODO: name the values.
    enum NextState {
        NEXT_STATE_0
    };

    static bool TryToChangeState(Hero* hero);

    StateSpaceJump(Hero* hero, NextState next);
    StateSpaceJump(Hero* hero, NextState next, hel::math::Vector3 pos);
};

}
}
}
}

#endif
