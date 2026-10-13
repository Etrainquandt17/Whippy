#ifndef SCN_STEP_HERO_HAMMER_STATEFLOATSPIN_H
#define SCN_STEP_HERO_HAMMER_STATEFLOATSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateFloatSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateFloatSpin(Hero* hero);
    virtual ~StateFloatSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqJumpEffect();

    bool mIsBubble;
    u32 mFrame;
};

}
}
}
}

#endif
