#ifndef SCN_STEP_BOSS_GIGANTEDGE_STATEGUARD_H
#define SCN_STEP_BOSS_GIGANTEDGE_STATEGUARD_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

class StateGuard : public StateBase {
public:
    StateGuard(Boss* boss);
    virtual ~StateGuard();
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
