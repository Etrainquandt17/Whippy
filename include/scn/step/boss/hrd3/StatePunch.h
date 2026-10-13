#ifndef SCN_STEP_BOSS_HRD3_STATEPUNCH_H
#define SCN_STEP_BOSS_HRD3_STATEPUNCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StatePunch : public StateBase {
public:
    StatePunch(Boss* boss, bool isStrong);
    virtual ~StatePunch();
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
