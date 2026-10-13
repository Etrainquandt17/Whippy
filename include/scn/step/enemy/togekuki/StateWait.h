#ifndef SCN_STEP_ENEMY_TOGEKUKI_STATEWAIT_H
#define SCN_STEP_ENEMY_TOGEKUKI_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace togekuki {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual void procMove();

private:
    u32 mFrame;
};

}
}
}
}

#endif
