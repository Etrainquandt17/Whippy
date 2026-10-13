#ifndef SCN_STEP_BOSS_HRD3PILOT_STATEWAIT_H
#define SCN_STEP_BOSS_HRD3PILOT_STATEWAIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

class StateWait : public StateBase {
public:
    StateWait(Boss* boss);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
