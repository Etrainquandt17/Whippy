#ifndef SCN_STEP_BOSS_LANDIA_STATEUNION_H
#define SCN_STEP_BOSS_LANDIA_STATEUNION_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateUnion : public StateBase {
public:
    StateUnion(Boss* boss);
    virtual ~StateUnion();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
