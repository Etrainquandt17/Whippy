#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONMOVE_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONMOVE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBalloonMove : public StateBase {
public:
    StateSwellBalloonMove(Boss* boss, u32 count);
    virtual ~StateSwellBalloonMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}
}
}
}

#endif
