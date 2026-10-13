#ifndef SCN_STEP_BOSS_LOWPER_STATEMOVETOFAR_H
#define SCN_STEP_BOSS_LOWPER_STATEMOVETOFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateMoveToFar : public StateBase {
public:
    StateMoveToFar(Boss* boss, f32 y);
    virtual ~StateMoveToFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mCount;
    hel::math::Vector3 mOffset;
};

}
}
}
}

#endif
