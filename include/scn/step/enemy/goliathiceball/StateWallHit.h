#ifndef SCN_STEP_ENEMY_GOLIATHICEBALL_STATEWALLHIT_H
#define SCN_STEP_ENEMY_GOLIATHICEBALL_STATEWALLHIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathiceball {

class StateWallHit : public StateBase {
public:
    StateWallHit(Enemy* enemy);
    virtual ~StateWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mEndFrame;
};

}
}
}
}

#endif
