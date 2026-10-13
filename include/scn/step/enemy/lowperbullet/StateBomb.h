#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATEBOMB_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATEBOMB_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateBomb : public StateBase {
public:
    StateBomb(Enemy* enemy);
    virtual ~StateBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallAccel;
};

}
}
}
}

#endif
