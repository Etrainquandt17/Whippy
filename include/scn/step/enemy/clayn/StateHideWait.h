#ifndef SCN_STEP_ENEMY_CLAYN_STATEHIDEWAIT_H
#define SCN_STEP_ENEMY_CLAYN_STATEHIDEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace clayn {

class StateHideWait : public StateBase {
public:
    StateHideWait(Enemy* enemy);
    virtual ~StateHideWait();
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
