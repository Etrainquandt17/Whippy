#ifndef SCN_STEP_BOSS_LOWPER_STATEREVERSEDIMENSION_H
#define SCN_STEP_BOSS_LOWPER_STATEREVERSEDIMENSION_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateReverseDimension : public StateBase {
public:
    StateReverseDimension(Boss* boss);
    virtual ~StateReverseDimension();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
