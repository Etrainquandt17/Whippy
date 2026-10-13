#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_STATEWALKSTEPBACK_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_STATEWALKSTEPBACK_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace knucklejoe {

// TODO: members.
class StateWalkStepBack : public IState {
public:
    StateWalkStepBack(Enemy* enemy);
    virtual ~StateWalkStepBack();
};

}
}
}
}

#endif
