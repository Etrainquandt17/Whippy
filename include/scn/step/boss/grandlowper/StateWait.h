#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEWAIT_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEWAIT_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateWait : public IState {
public:
    StateWait(Boss* boss);
    virtual ~StateWait();
};

}

}
}
}

#endif
