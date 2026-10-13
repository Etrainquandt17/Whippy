#ifndef SCN_STEP_BOSS_HRD3_STATEMISSILEFAR_H
#define SCN_STEP_BOSS_HRD3_STATEMISSILEFAR_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace hrd3 {

// TODO: members.
class StateMissileFar : public IState {
public:
    StateMissileFar(Boss* boss, u32 _1);
    virtual ~StateMissileFar();
};

}
}
}
}

#endif
