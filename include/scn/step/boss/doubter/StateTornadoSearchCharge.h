#ifndef SCN_STEP_BOSS_DOUBTER_STATETORNADOSEARCHCHARGE_H
#define SCN_STEP_BOSS_DOUBTER_STATETORNADOSEARCHCHARGE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateTornadoSearchCharge : public StateBase {
public:
    StateTornadoSearchCharge(Boss* boss, u32 frame, u32 searchFrame, f32 rate);
    virtual ~StateTornadoSearchCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mSearchFrame;
    f32 mRate;
    u32 mCount;
    f32 mDecel;
};

}
}
}
}

#endif
