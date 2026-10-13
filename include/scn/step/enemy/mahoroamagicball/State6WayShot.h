#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATE6WAYSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATE6WAYSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class State6WayShot : public StateBase {
public:
    State6WayShot(Enemy* enemy);
    virtual ~State6WayShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
