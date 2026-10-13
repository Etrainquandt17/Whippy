#ifndef SCN_STEP_ENEMY_BARBAR_STATEMISS_H
#define SCN_STEP_ENEMY_BARBAR_STATEMISS_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barbar {

class StateMiss : public StateBase {
public:
    StateMiss(Enemy* enemy);
    virtual void procAnim();
};

}
}
}
}

#endif
