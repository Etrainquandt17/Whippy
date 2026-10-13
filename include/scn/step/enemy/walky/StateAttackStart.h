#ifndef SCN_STEP_ENEMY_WALKY_STATEATTACKSTART_H
#define SCN_STEP_ENEMY_WALKY_STATEATTACKSTART_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walky {

class StateAttackStart : public StateBase {
public:
    StateAttackStart(Enemy* enemy);
    virtual ~StateAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsRightDir;
    bool _d;
};

}
}
}
}

#endif
