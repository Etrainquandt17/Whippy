#ifndef SCN_STEP_ENEMY_LUPA_STATEMOVEAROUNDATTACK_H
#define SCN_STEP_ENEMY_LUPA_STATEMOVEAROUNDATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lupa {

class StateMoveAroundAttack : public StateBase {
public:
    StateMoveAroundAttack(Enemy* enemy);
    virtual ~StateMoveAroundAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mWaitFrame;
    u32 mAttackFrame;
    bool mIsRight;
    f32 mRange;
    u32 mWaitLength;
};

}
}
}
}

#endif
