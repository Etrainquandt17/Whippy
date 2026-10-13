#ifndef SCN_STEP_BOSS_DUBIOR_STATEMOVETHUNDERSTART_H
#define SCN_STEP_BOSS_DUBIOR_STATEMOVETHUNDERSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateMoveThunderStart : public StateBase {
public:
    StateMoveThunderStart(Boss* boss);
    virtual ~StateMoveThunderStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mTargetPos;
};

}
}
}
}

#endif
