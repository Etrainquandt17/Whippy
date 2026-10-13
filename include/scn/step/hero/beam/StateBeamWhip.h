#ifndef SCN_STEP_HERO_BEAM_STATEBEAMWHIP_H
#define SCN_STEP_HERO_BEAM_STATEBEAMWHIP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

class StateBeamWhip : public StateBase {
public:
    StateBeamWhip(Hero* hero);
    virtual ~StateBeamWhip();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void procAnimWhip();
    void procAnimRevolution();

    u32 mFrame;
    f32 _C;
    bool mIsRight;
    u32 mPushCount;
    u32 mWait;
    f32 mPrevFrame;
    bool mIsEnd;
    int mStep;
};

}
}
}
}

#endif
