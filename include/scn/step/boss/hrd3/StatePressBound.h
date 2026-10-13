#ifndef SCN_STEP_BOSS_HRD3_STATEPRESSBOUND_H
#define SCN_STEP_BOSS_HRD3_STATEPRESSBOUND_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StatePressBound : public StateBase {
public:
    StatePressBound(Boss* boss, u32 frame);
    virtual ~StatePressBound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setTargetPos();
    void reqBoundEffect();

    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsLast;
};

}
}
}
}

#endif
