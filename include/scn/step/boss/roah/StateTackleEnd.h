#ifndef SCN_STEP_BOSS_ROAH_STATETACKLEEND_H
#define SCN_STEP_BOSS_ROAH_STATETACKLEEND_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateTackleEnd : public StateBase {
public:
    StateTackleEnd(Boss* boss);
    virtual ~StateTackleEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
};

}
}
}
}

#endif
