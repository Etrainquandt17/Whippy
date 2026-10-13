#ifndef SCN_STEP_ENEMY_BARRACU_STATESWIMSTRAIGHT_H
#define SCN_STEP_ENEMY_BARRACU_STATESWIMSTRAIGHT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barracu {

class StateSwimStraight : public StateBase {
public:
    StateSwimStraight(Enemy* enemy);
    virtual ~StateSwimStraight();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
};

}
}
}
}

#endif
