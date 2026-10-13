#ifndef SCN_STEP_ENEMY_PACTO_STATEEAT_H
#define SCN_STEP_ENEMY_PACTO_STATEEAT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pacto {

class StateEat : public StateBase {
public:
    StateEat(Enemy* enemy);
    virtual ~StateEat();
    virtual void procAnim();

private:
    u32 mFrame;
    int mDamageWait;
};

}
}
}
}

#endif
