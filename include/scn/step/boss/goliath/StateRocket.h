#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKET_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKET_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateRocket : public IState {
public:
    StateRocket(Boss* boss, f32 _1, u32 _2, bool _3);
    virtual ~StateRocket();
};

}
}
}
}

#endif
