#ifndef SCN_STEP_HERO_DAMAGE_STATEFIRELV2_H
#define SCN_STEP_HERO_DAMAGE_STATEFIRELV2_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateFireLv2 : public StateBase {
public:
    StateFireLv2(Hero* hero);
    virtual ~StateFireLv2();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    bool mIsLanded;
    u32 mWait;
    u32 mFrame;
};

}
}
}
}

#endif
