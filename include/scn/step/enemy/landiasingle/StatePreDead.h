#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEPREDEAD_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEPREDEAD_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StatePreDead : public StateBase {
public:
    StatePreDead(Enemy* enemy);
    virtual ~StatePreDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFlashFrame;
    u32 mFrame;
};

}
}
}
}

#endif
