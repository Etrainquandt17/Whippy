#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATECANNONEND_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATECANNONEND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateCannonEnd : public StateBase {
public:
    StateCannonEnd(Boss* boss, f32 angle);
    virtual ~StateCannonEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateSRT();

    f32 mAngle;
};

}
}
}
}

#endif
