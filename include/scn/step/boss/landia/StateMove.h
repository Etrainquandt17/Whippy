#ifndef SCN_STEP_BOSS_LANDIA_STATEMOVE_H
#define SCN_STEP_BOSS_LANDIA_STATEMOVE_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateMove : public StateBase {
public:
    struct Config {
        u32 _0;
        hel::math::Vector2 _4;
    };

    StateMove(Boss* boss, Config config);
    virtual ~StateMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
    Config mConfig;
};

}
}
}
}

#endif
