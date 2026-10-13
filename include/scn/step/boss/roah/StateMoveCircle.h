#ifndef SCN_STEP_BOSS_ROAH_STATEMOVECIRCLE_H
#define SCN_STEP_BOSS_ROAH_STATEMOVECIRCLE_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateMoveCircle : public StateBase {
public:
    struct Config {
        u32 _0;
        f32 _4;
        f32 _8;
        f32 _C;
    };

    StateMoveCircle(Boss* boss, Config config);
    virtual ~StateMoveCircle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mBasePos;
    u32 mCount;
    Config mConfig;
};

}
}
}
}

#endif
