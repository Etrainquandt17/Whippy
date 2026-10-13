#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_STATEFALL_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whispyapple {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy, u32 count = 0xFFFFFFFF, bool flag = false);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallSpeed;
    u32 mCount;
    bool mFlag;
};

}
}
}
}

#endif
