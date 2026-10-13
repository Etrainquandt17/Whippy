#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEJUMP_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/JumpDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateJump : public StateBase {
public:
    StateJump(Boss* boss, const JumpDesc& desc);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsStart;
};

}
}
}
}

#endif
