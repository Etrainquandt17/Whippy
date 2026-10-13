#ifndef SCN_STEP_HERO_BEAM_STATEBEAMCYCLEBEAM_H
#define SCN_STEP_HERO_BEAM_STATEBEAMCYCLEBEAM_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

class StateBeamCycleBeam : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateBeamCycleBeam(Hero* hero);
    virtual ~StateBeamCycleBeam();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    bool mIsFirst;
};

}
}
}
}

#endif
