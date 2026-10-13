#ifndef SCN_STEP_ENEMY_CRABY_STATEATTACK_H
#define SCN_STEP_ENEMY_CRABY_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace craby {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procFixPos();

private:
    void setNextState();
    
    bool mIsLeft;
};

}
}
}
}

#endif
