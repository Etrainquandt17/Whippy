#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATESHARPSHOOTSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATESHARPSHOOTSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateSharpshootShot : public StateBase {
public:
    StateSharpshootShot(Enemy* enemy);
    virtual ~StateSharpshootShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
