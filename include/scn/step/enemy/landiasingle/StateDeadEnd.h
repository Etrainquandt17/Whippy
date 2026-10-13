#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEDEADEND_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEDEADEND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateDeadEnd : public StateBase {
public:
    StateDeadEnd(Enemy* enemy);
    virtual ~StateDeadEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
