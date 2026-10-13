#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATEWARP_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATEWARP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateWarp : public StateBase {
public:
    StateWarp(Enemy* enemy);
    virtual ~StateWarp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
