#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATECAMERAOUTWAIT_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATECAMERAOUTWAIT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateCameraOutWait : public StateBase {
public:
    StateCameraOutWait(Boss* boss, u32 frame, f32 height);
    virtual ~StateCameraOutWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
};

}
}
}
}

#endif
