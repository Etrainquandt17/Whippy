#ifndef SCN_STEP_ENEMY_WALF_STATEMOVEONWATER_H
#define SCN_STEP_ENEMY_WALF_STATEMOVEONWATER_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walf {

// TODO: members.
class StateMoveOnWater : public IState {
public:
    StateMoveOnWater(Enemy* enemy);
    virtual ~StateMoveOnWater();
};

}
}
}
}

#endif
