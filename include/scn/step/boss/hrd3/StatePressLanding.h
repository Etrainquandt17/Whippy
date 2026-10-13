#ifndef SCN_STEP_BOSS_HRD3_STATEPRESSLANDING_H
#define SCN_STEP_BOSS_HRD3_STATEPRESSLANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StatePressLanding : public StateBase {
public:
    StatePressLanding(Boss* boss);
    virtual ~StatePressLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqStar();
};

}
}
}
}

#endif
