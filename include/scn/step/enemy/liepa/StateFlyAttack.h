#ifndef SCN_STEP_ENEMY_LIEPA_STATEFLYATTACK_H
#define SCN_STEP_ENEMY_LIEPA_STATEFLYATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace liepa {

class StateFlyAttack : public StateBase {
public:
    StateFlyAttack(Enemy* enemy);
    virtual ~StateFlyAttack();
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
