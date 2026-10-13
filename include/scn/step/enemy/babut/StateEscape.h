#ifndef SCN_STEP_ENEMY_BABUT_STATEESCAPE_H
#define SCN_STEP_ENEMY_BABUT_STATEESCAPE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateEscape : public StateBase {
public:
    StateEscape(Enemy* enemy);
    virtual void procMove();
};

}
}
}
}

#endif
