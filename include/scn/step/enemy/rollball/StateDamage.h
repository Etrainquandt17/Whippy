#ifndef SCN_STEP_ENEMY_ROLLBALL_STATEDAMAGE_H
#define SCN_STEP_ENEMY_ROLLBALL_STATEDAMAGE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rollball {

class StateDamage : public StateBase {
public:
    StateDamage(Enemy* enemy);
    virtual void procAnim();
};

}
}
}
}

#endif
