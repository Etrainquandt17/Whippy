#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBEAMSWORDDASH_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBEAMSWORDDASH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBeamSwordDash : public StateBase {
public:
    StateBeamSwordDash(Boss* boss);
    virtual ~StateBeamSwordDash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    // TODO: name the phases.
    enum Phase {
        PHASE_0,
        PHASE_1,
        PHASE_2,
        PHASE_3,
        PHASE_4
    };

    void reqStar();

    Phase mPhase;
    u32 mCount;
};

}
}
}
}

#endif
