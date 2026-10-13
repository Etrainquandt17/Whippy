#ifndef SCN_STEP_ENEMY_TICK_STATESKIP_H
#define SCN_STEP_ENEMY_TICK_STATESKIP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tick {

class StateSkip : public StateBase {
public:
    StateSkip(Enemy* enemy);
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
