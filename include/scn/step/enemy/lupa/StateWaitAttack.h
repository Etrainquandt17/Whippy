#ifndef SCN_STEP_ENEMY_LUPA_STATEWAITATTACK_H
#define SCN_STEP_ENEMY_LUPA_STATEWAITATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lupa {

class StateWaitAttack : public StateBase {
public:
    StateWaitAttack(Enemy* enemy);
    virtual ~StateWaitAttack();
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
