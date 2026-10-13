#ifndef SCN_STEP_BOSS_HRD3_STATEWAITFAR_H
#define SCN_STEP_BOSS_HRD3_STATEWAITFAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateWaitFar : public StateBase {
public:
    StateWaitFar(Boss* boss);
    virtual ~StateWaitFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
