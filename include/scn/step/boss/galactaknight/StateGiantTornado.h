#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEGIANTTORNADO_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEGIANTTORNADO_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateGiantTornado : public StateBase {
public:
    StateGiantTornado(Boss* boss, u32 frame, f32 speed);
    virtual ~StateGiantTornado();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqTornado();
    u32 mFrame;
    u32 mCount;
    f32 mSpeed;
};

}
}
}
}

#endif
