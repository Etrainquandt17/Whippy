#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEGRANDMAGICBALL_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEGRANDMAGICBALL_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateGrandMagicBall : public IState {
public:
    StateGrandMagicBall(Boss* boss);
    virtual ~StateGrandMagicBall();
};

}

}
}
}

#endif
