#ifndef SCN_STEP_HERO_BEAM_STATEBEAMWAVESHOT_H
#define SCN_STEP_HERO_BEAM_STATEBEAMWAVESHOT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

class StateBeamWaveShot : public StateBase {
public:
    StateBeamWaveShot(Hero* hero);
    virtual ~StateBeamWaveShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsRight;
};

}
}
}
}

#endif
