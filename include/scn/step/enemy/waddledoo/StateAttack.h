#ifndef SCN_STEP_ENEMY_WADDLEDOO_STATEATTACK_H
#define SCN_STEP_ENEMY_WADDLEDOO_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();
};

}
}
}
}

#endif
