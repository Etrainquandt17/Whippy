#ifndef SCN_STEP_ENEMY_BABUT_STATEPURSUIT_H
#define SCN_STEP_ENEMY_BABUT_STATEPURSUIT_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

// TODO: members.
class StatePursuit : public IState {
public:
    StatePursuit(Enemy* enemy);
    virtual ~StatePursuit();
};

}
}
}
}

#endif
