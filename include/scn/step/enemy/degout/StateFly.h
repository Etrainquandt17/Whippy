#ifndef SCN_STEP_ENEMY_DEGOUT_STATEFLY_H
#define SCN_STEP_ENEMY_DEGOUT_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace degout {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual void procAnim();

private:
    u32 mFrame;
};

}
}
}
}

#endif
