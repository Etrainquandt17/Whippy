#ifndef SCN_STEP_ENEMY_ROCKY_STATECLIFFATTACK_H
#define SCN_STEP_ENEMY_ROCKY_STATECLIFFATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateCliffAttack : public StateBase {
public:
    StateCliffAttack(Enemy* enemy);
    virtual ~StateCliffAttack();
    virtual void procAnim();
    virtual void procFixPos();

private:
    s32 mFrame;
};

}
}
}
}

#endif
