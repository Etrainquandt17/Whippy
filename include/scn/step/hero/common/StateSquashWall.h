#ifndef SCN_STEP_HERO_COMMON_STATESQUASHWALL_H
#define SCN_STEP_HERO_COMMON_STATESQUASHWALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSquashWall : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSquashWall(Hero* hero);
    virtual ~StateSquashWall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
