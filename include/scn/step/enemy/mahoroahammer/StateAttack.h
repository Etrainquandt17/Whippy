#ifndef SCN_STEP_ENEMY_MAHOROAHAMMER_STATEATTACK_H
#define SCN_STEP_ENEMY_MAHOROAHAMMER_STATEATTACK_H

#include "scn/step/enemy/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroahammer {

// TODO: members.
class StateAttack : public IState {
public:
    StateAttack(Enemy* enemy, f32 speed, u32 count);
    virtual ~StateAttack();
};

}
}
}
}

#endif
