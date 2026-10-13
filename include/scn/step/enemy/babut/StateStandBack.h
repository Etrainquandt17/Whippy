#ifndef SCN_STEP_ENEMY_BABUT_STATESTANDBACK_H
#define SCN_STEP_ENEMY_BABUT_STATESTANDBACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateStandBack : public StateBase {
public:
    StateStandBack(Enemy* enemy);
    virtual ~StateStandBack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
