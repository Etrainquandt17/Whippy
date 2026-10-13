#ifndef SCN_STEP_BOSS_ROAH_STATETACKLE_H
#define SCN_STEP_BOSS_ROAH_STATETACKLE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateTackle : public StateBase {
public:
    struct Config {
        u32 _0;
        f32 _4;
        f32 _8;
    };

    StateTackle(Boss* boss, Config config);
    virtual ~StateTackle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 _C;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    Config mConfig;
    f32 mBaseRotX;
    f32 mPrevRate;
};

}
}
}
}

#endif
