#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEDASH_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEDASH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateDash : public StateBase {
public:
    StateDash(Boss* boss, f32 speed, f32 distance);
    virtual ~StateDash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeed;
    f32 mDistance;
    bool mIsMove;
};

}
}
}
}

#endif
