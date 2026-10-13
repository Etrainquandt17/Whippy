#ifndef SCN_STEP_ENEMY_ROCKY_STATESTAY_H
#define SCN_STEP_ENEMY_ROCKY_STATESTAY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateStay : public StateBase {
public:
    StateStay(Enemy* enemy);
    virtual ~StateStay();
    virtual void procAnim();
    virtual void procFixPos();

private:
    s32 mFrame;
    s32 mAttackFrame;
};

}
}
}
}

#endif
