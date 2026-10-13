#ifndef SCN_STEP_ENEMY_WAPOD_STATERISE_H
#define SCN_STEP_ENEMY_WAPOD_STATERISE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace wapod {

class StateRise : public StateBase {
public:
    StateRise(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
