#ifndef SCN_STEP_BOSS_LOWPER_STATEFIRETACKLERESTART_H
#define SCN_STEP_BOSS_LOWPER_STATEFIRETACKLERESTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFireTackleRestart : public StateBase {
public:
    StateFireTackleRestart(Boss* boss, u32 frame, u32 _3);
    virtual ~StateFireTackleRestart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 _C;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRotY;
};

}
}
}
}

#endif
