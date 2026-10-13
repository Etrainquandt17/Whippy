#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEHOMINGSHOT_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEHOMINGSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

class StateHomingShot : public StateBase {
public:
    StateHomingShot(Enemy* enemy);
    virtual ~StateHomingShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
