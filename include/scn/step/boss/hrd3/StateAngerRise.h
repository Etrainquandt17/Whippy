#ifndef SCN_STEP_BOSS_HRD3_STATEANGERRISE_H
#define SCN_STEP_BOSS_HRD3_STATEANGERRISE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateAngerRise : public StateBase {
public:
    StateAngerRise(Boss* boss);
    virtual ~StateAngerRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    f32 mGoalY;
    bool mIsMove;
};

}
}
}
}

#endif
