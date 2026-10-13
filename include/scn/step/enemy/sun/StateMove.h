#ifndef SCN_STEP_ENEMY_SUN_STATEMOVE_H
#define SCN_STEP_ENEMY_SUN_STATEMOVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sun {

// TODO: stub
class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
};

}
}
}
}

#endif
