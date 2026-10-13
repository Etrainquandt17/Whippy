#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEFAR_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEFAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleFar : public StateBase {
public:
    StateTackleFar(Boss* boss);
    virtual ~StateTackleFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mSwayCount;
    f32 mStartY;
    f32 mGoalY;
    f32 mX;
    f32 mSway;
};

}
}
}
}

#endif
