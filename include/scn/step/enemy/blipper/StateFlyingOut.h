#ifndef SCN_STEP_ENEMY_BLIPPER_STATEFLYINGOUT_H
#define SCN_STEP_ENEMY_BLIPPER_STATEFLYINGOUT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace blipper {

class StateFlyingOut : public StateBase {
public:
    StateFlyingOut(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
