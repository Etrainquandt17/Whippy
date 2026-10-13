#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEFARROLLING_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEFARROLLING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleFarRolling : public StateBase {
public:
    StateTackleFarRolling(Boss* boss);
    virtual ~StateTackleFarRolling();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mStartY;
    f32 mGoalY;
    f32 mX;
    f32 mRotX;
    f32 mRotY;
    f32 mRotSpeed;
};

}
}
}
}

#endif
