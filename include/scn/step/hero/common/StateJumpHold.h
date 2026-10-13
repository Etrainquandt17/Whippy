#ifndef SCN_STEP_HERO_COMMON_STATEJUMPHOLD_H
#define SCN_STEP_HERO_COMMON_STATEJUMPHOLD_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateJumpHold : public StateBase {
public:
    StateJumpHold(Hero* hero, bool);
    virtual ~StateJumpHold();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool _8;
    u32 mFrame;
};

}
}
}
}

#endif
