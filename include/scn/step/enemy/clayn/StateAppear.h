#ifndef SCN_STEP_ENEMY_CLAYN_STATEAPPEAR_H
#define SCN_STEP_ENEMY_CLAYN_STATEAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace clayn {

class StateAppear : public StateBase {
public:
    StateAppear(Enemy* enemy);
    virtual ~StateAppear();
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
