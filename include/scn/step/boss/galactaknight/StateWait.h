#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEWAIT_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEWAIT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

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
