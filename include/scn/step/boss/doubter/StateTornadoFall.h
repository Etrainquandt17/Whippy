#ifndef SCN_STEP_BOSS_DOUBTER_STATETORNADOFALL_H
#define SCN_STEP_BOSS_DOUBTER_STATETORNADOFALL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateTornadoFall : public StateBase {
public:
    StateTornadoFall(Boss* boss);
    virtual ~StateTornadoFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setInitSpeed();
};

}
}
}
}

#endif
