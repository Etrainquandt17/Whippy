#ifndef SCN_STEP_ENEMY_OWGULF_STATEATTACK1WAY_H
#define SCN_STEP_ENEMY_OWGULF_STATEATTACK1WAY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace owgulf {

class StateAttack1Way : public StateBase {
public:
    StateAttack1Way(Enemy* enemy);
    virtual void procAnim();

private:
    u32 mFrame;
};

}
}
}
}

#endif
