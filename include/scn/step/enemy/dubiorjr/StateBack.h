#ifndef SCN_STEP_ENEMY_DUBIORJR_STATEBACK_H
#define SCN_STEP_ENEMY_DUBIORJR_STATEBACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace dubiorjr {

class StateBack : public StateBase {
public:
    StateBack(Enemy* enemy, f32 rot);
    virtual ~StateBack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
