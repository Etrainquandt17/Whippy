#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATETHUNDERSPINE_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATETHUNDERSPINE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateThunderSpine : public StateBase {
public:
    StateThunderSpine(Boss* boss);
    virtual ~StateThunderSpine();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
