#ifndef SCN_STEP_BOSS_LANDIA_STATEGLIDESTART_H
#define SCN_STEP_BOSS_LANDIA_STATEGLIDESTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateGlideStart : public StateBase {
public:
    StateGlideStart(Boss* boss);
    virtual ~StateGlideStart();
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
