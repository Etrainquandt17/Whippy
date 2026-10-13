#ifndef SCN_STEP_ENEMY_JUCKLE_STATEFOLLOW_H
#define SCN_STEP_ENEMY_JUCKLE_STATEFOLLOW_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace juckle {

// TODO: members.
class StateFollow : public IState {
public:
    StateFollow(Enemy* enemy);
    virtual ~StateFollow();
};

}
}
}
}

#endif
