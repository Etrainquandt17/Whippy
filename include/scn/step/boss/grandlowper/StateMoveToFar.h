#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEMOVETOFAR_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEMOVETOFAR_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateMoveToFar : public IState {
public:
    StateMoveToFar(Boss* boss);
    virtual ~StateMoveToFar();
};

}

}
}
}

#endif
