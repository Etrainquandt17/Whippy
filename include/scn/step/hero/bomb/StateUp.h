#ifndef SCN_STEP_HERO_BOMB_STATEUP_H
#define SCN_STEP_HERO_BOMB_STATEUP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

class StateUp : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, GearBombController& controller);

    StateUp(Hero* hero, GearBombController& controller);
    virtual ~StateUp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    GearBombController& mController;
    u32 mFrame;
};

}
}
}
}

#endif
