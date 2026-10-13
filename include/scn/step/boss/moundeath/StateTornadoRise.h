#ifndef SCN_STEP_BOSS_MOUNDEATH_STATETORNADORISE_H
#define SCN_STEP_BOSS_MOUNDEATH_STATETORNADORISE_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateTornadoRise : public StateBase {
public:
    StateTornadoRise(Boss* boss);
    virtual ~StateTornadoRise();
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
