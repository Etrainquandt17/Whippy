#ifndef SCN_STEP_ENEMY_GIGATZO_STATEATTACK_H
#define SCN_STEP_ENEMY_GIGATZO_STATEATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gigatzo {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void shot();
    hel::math::Vector2 setBulletInitVel();
    
    u32 mFrame;
};

}
}
}
}

#endif
