#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEMINCE_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEMINCE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateMince : public StateBase {
public:
    StateMince(Boss* boss);
    virtual ~StateMince();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();
};

}
}
}
}

#endif
