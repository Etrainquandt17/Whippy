#ifndef SCN_STEP_BOSS_LOWPER_STATEGLIDESHOT_H
#define SCN_STEP_BOSS_LOWPER_STATEGLIDESHOT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateGlideShot : public StateBase {
public:
    StateGlideShot(Boss* boss, u32 frame);
    virtual ~StateGlideShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    u32 mShotCount;
    f32 mStartY;
    f32 mGoalY;
    f32 mGoalX;
    f32 mStartX;
};

}
}
}
}

#endif
