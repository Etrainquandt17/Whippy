#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_STATEHADOU_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_STATEHADOU_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace knucklejoe {

class StateHadou : public StateBase {
public:
    StateHadou(Enemy* enemy);
    virtual ~StateHadou();
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
