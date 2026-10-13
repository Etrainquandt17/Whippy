#ifndef SCN_STEP_BOSS_LOWPER_STATEREFLECTHOMINGSHOT_H
#define SCN_STEP_BOSS_LOWPER_STATEREFLECTHOMINGSHOT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateReflectHomingShot : public StateBase {
public:
    StateReflectHomingShot(Boss* boss);
    virtual ~StateReflectHomingShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqShotBullet();
    u32 mCount;
    u32 mPhase;
    u32 _10;
};

}
}
}
}

#endif
