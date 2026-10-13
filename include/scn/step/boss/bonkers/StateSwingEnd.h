#ifndef SCN_STEP_BOSS_BONKERS_STATESWINGEND_H
#define SCN_STEP_BOSS_BONKERS_STATESWINGEND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateSwingEnd : public StateBase {
public:
    StateSwingEnd(Boss* boss);
    virtual ~StateSwingEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
