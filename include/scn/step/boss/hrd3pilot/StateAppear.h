#ifndef SCN_STEP_BOSS_HRD3PILOT_STATEAPPEAR_H
#define SCN_STEP_BOSS_HRD3PILOT_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

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
