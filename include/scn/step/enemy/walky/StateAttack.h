#ifndef SCN_STEP_ENEMY_WALKY_STATEATTACK_H
#define SCN_STEP_ENEMY_WALKY_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walky {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void shotAll();
    void shot(u32 variation);
    
    u32 mFrame;
    bool mIsShot;
};

}
}
}
}

#endif
