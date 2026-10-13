#ifndef SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSRISE_H
#define SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSRISE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateFlyingBodyPressRise : public StateBase {
public:
    StateFlyingBodyPressRise(Boss* boss);
    virtual ~StateFlyingBodyPressRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setTargetPos();

    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsMove;
};

}
}
}
}

#endif
