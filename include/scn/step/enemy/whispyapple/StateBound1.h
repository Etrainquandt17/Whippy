#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUND1_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUND1_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whispyapple {

class StateBound1 : public StateBase {
public:
    StateBound1(Enemy* enemy, u32 count, bool flag);
    virtual ~StateBound1();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallSpeed;
    f32 mFallAccel;
    f32 mRot;
    bool mIsRising;
    u32 mCount;
    bool mFlag;
};

}
}
}
}

#endif
