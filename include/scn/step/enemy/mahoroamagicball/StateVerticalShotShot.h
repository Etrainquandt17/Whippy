#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEVERTICALSHOTSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEVERTICALSHOTSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateVerticalShotShot : public StateBase {
public:
    StateVerticalShotShot(Enemy* enemy);
    virtual ~StateVerticalShotShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
