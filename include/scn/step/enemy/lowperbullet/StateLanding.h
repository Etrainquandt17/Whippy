#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATELANDING_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATELANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateLanding : public StateBase {
public:
    StateLanding(Enemy* enemy);
    virtual ~StateLanding();
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
