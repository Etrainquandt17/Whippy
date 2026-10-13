#ifndef SCN_STEP_ENEMY_FATTYBUFFERJR_STATEESCAPENEAR_H
#define SCN_STEP_ENEMY_FATTYBUFFERJR_STATEESCAPENEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace fattybufferjr {

class StateEscapeNear : public StateBase {
public:
    StateEscapeNear(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
