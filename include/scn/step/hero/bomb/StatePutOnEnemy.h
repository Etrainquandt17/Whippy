#ifndef SCN_STEP_HERO_BOMB_STATEPUTONENEMY_H
#define SCN_STEP_HERO_BOMB_STATEPUTONENEMY_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

class StatePutOnEnemy : public StateBase {
public:
    StatePutOnEnemy(Hero* hero, GearBombController& controller);
    virtual ~StatePutOnEnemy();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

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
