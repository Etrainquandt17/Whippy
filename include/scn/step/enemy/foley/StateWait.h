#ifndef SCN_STEP_ENEMY_FOLEY_STATEWAIT_H
#define SCN_STEP_ENEMY_FOLEY_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace foley {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();

private:
    bool mIsReady;
};

}
}
}
}

#endif
