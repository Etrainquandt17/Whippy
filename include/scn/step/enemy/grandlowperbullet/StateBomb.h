#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEBOMB_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEBOMB_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

class StateBomb : public StateBase {
public:
    StateBomb(Enemy* enemy);
    virtual ~StateBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsLanded;
    f32 mFallAccel;
    u32 mFrame;
};

}
}
}
}

#endif
