#ifndef SCN_STEP_ENEMY_GOLIATHSNOWBALL_STATEFALL_H
#define SCN_STEP_ENEMY_GOLIATHSNOWBALL_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathsnowball {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}
}
}
}

#endif
