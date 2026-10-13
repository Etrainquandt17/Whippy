#ifndef SCN_STEP_ENEMY_LEAFAN_STATEFALL_H
#define SCN_STEP_ENEMY_LEAFAN_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace leafan {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
