#ifndef SCN_STEP_ENEMY_STAREFFECT_STATEPUFF_H
#define SCN_STEP_ENEMY_STAREFFECT_STATEPUFF_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace stareffect {

class StatePuff : public StateBase {
public:
    StatePuff(Enemy* enemy);
    virtual ~StatePuff();
    virtual void procAnim();
    virtual void procMove();
};

}
}
}
}

#endif
