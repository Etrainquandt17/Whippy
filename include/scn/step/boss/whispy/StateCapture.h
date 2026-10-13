#ifndef SCN_STEP_BOSS_WHISPY_STATECAPTURE_H
#define SCN_STEP_BOSS_WHISPY_STATECAPTURE_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateCapture : public StateBase {
public:
    StateCapture(Boss* boss);
    virtual ~StateCapture();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
