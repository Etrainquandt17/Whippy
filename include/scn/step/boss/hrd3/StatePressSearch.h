#ifndef SCN_STEP_BOSS_HRD3_STATEPRESSSEARCH_H
#define SCN_STEP_BOSS_HRD3_STATEPRESSSEARCH_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StatePressSearch : public StateBase {
public:
    StatePressSearch(Boss* boss, u32 frame, u32 boundCount);
    virtual ~StatePressSearch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    u32 mBoundCount;
    f32 mStartX;
    hel::math::Vector3 mGoalPos;
};

}
}
}
}

#endif
