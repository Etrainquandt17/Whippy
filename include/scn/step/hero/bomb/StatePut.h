#ifndef SCN_STEP_HERO_BOMB_STATEPUT_H
#define SCN_STEP_HERO_BOMB_STATEPUT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

class StatePut : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, GearBombController& controller);

    StatePut(Hero* hero, GearBombController& controller);
    virtual ~StatePut();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void put();

    GearBombController& mController;
    u32 mFrame;
};

}
}
}
}

#endif
