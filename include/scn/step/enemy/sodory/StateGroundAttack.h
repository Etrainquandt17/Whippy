#ifndef SCN_STEP_ENEMY_SODORY_STATEGROUNDATTACK_H
#define SCN_STEP_ENEMY_SODORY_STATEGROUNDATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sodory {

class StateGroundAttack : public StateBase {
public:
    StateGroundAttack(Enemy* enemy);
    virtual ~StateGroundAttack();
    virtual void procAnim();
    virtual void procMove();

private:
    bool mIsRightDir;
};

}
}
}
}

#endif
