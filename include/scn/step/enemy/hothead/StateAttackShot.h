#ifndef SCN_STEP_ENEMY_HOTHEAD_STATEATTACKSHOT_H
#define SCN_STEP_ENEMY_HOTHEAD_STATEATTACKSHOT_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace hothead {

// TODO: members.
class StateAttackShot : public IState {
public:
    StateAttackShot(Enemy* enemy);
    virtual ~StateAttackShot();
};

}
}
}
}

#endif
