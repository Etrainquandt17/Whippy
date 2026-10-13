#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEGROUND_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEGROUND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleGround : public StateBase {
public:
    StateTackleGround(Boss* boss, u32 frame, f32 distance);
    virtual ~StateTackleGround();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    f32 mY;
    f32 mStartX;
    f32 mGoalX;
};

}
}
}
}

#endif
