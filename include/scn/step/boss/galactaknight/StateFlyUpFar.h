#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEFLYUPFAR_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEFLYUPFAR_H

#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateFlyUpFar : public StateBase {
public:
    StateFlyUpFar(Boss* boss, f32 height, f32 arc);
    virtual ~StateFlyUpFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    hel::math::Direction3 mDir;
    f32 mHeight;
    f32 mArc;
};

}
}
}
}

#endif
