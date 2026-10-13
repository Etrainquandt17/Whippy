#ifndef SCN_STEP_ENEMY_PARASOL_STATELINK_H
#define SCN_STEP_ENEMY_PARASOL_STATELINK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace parasol {

class StateLink : public StateBase {
public:
    StateLink(Enemy* enemy);
    virtual void procAnim();
};

}
}
}
}

#endif
