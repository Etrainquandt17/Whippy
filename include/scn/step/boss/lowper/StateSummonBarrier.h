#ifndef SCN_STEP_BOSS_LOWPER_STATESUMMONBARRIER_H
#define SCN_STEP_BOSS_LOWPER_STATESUMMONBARRIER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSummonBarrier : public StateBase {
public:
    StateSummonBarrier(Boss* boss);
    virtual ~StateSummonBarrier();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
