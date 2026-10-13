#ifndef SCN_STEP_BOSS_ROAH_STATEOAREND_H
#define SCN_STEP_BOSS_ROAH_STATEOAREND_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateOarEnd : public StateBase {
public:
    StateOarEnd(Boss* boss);
    virtual ~StateOarEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsTriggered;
};

}
}
}
}

#endif
