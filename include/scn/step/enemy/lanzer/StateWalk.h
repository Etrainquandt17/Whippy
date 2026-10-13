#ifndef SCN_STEP_ENEMY_LANZER_STATEWALK_H
#define SCN_STEP_ENEMY_LANZER_STATEWALK_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lanzer {

// TODO: members.
class StateWalk : public IState {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
};

}
}
}
}

#endif
