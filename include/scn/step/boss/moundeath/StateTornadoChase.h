#ifndef SCN_STEP_BOSS_MOUNDEATH_STATETORNADOCHASE_H
#define SCN_STEP_BOSS_MOUNDEATH_STATETORNADOCHASE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateTornadoChase : public StateBase {
public:
    StateTornadoChase(Boss* boss);
    virtual ~StateTornadoChase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mWait;
    hel::math::Vector3 mDir;
};

}
}
}
}

#endif
