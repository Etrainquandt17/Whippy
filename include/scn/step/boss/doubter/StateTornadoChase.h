#ifndef SCN_STEP_BOSS_DOUBTER_STATETORNADOCHASE_H
#define SCN_STEP_BOSS_DOUBTER_STATETORNADOCHASE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateTornadoChase : public StateBase {
public:
    StateTornadoChase(Boss* boss, u32 frame);
    virtual ~StateTornadoChase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mDir;
};

}
}
}
}

#endif
