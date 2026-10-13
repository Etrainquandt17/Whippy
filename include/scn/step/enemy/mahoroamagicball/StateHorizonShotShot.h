#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHORIZONSHOTSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHORIZONSHOTSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateHorizonShotShot : public StateBase {
public:
    StateHorizonShotShot(Enemy* enemy);
    virtual ~StateHorizonShotShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
