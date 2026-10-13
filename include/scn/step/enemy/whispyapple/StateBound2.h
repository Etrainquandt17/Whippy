#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUND2_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUND2_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whispyapple {

class StateBound2 : public StateBase {
public:
    StateBound2(Enemy* enemy, u32 count, bool flag);
    virtual ~StateBound2();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    u32 mCount;
    bool mFlag;
};

}
}
}
}

#endif
