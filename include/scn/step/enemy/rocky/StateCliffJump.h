#ifndef SCN_STEP_ENEMY_ROCKY_STATECLIFFJUMP_H
#define SCN_STEP_ENEMY_ROCKY_STATECLIFFJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateCliffJump : public StateBase {
public:
    StateCliffJump(Enemy* enemy);
    virtual ~StateCliffJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    s32 mFrame;
};

}
}
}
}

#endif
