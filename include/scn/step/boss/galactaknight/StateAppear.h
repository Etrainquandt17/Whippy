#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEAPPEAR_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
