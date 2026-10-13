#ifndef SCN_STEP_ENEMY_DUBIORJR_STATEFLY_H
#define SCN_STEP_ENEMY_DUBIORJR_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace dubiorjr {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy, f32 rot);
    virtual ~StateFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
