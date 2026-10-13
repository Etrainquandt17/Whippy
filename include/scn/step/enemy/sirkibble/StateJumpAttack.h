#ifndef SCN_STEP_ENEMY_SIRKIBBLE_STATEJUMPATTACK_H
#define SCN_STEP_ENEMY_SIRKIBBLE_STATEJUMPATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sirkibble {

class StateJumpAttack : public StateBase {
public:
    StateJumpAttack(Enemy* enemy);
    virtual ~StateJumpAttack();
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
