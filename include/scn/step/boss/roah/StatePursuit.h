#ifndef SCN_STEP_BOSS_ROAH_STATEPURSUIT_H
#define SCN_STEP_BOSS_ROAH_STATEPURSUIT_H

#include "gobj/MoveParam.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StatePursuit : public StateBase {
public:
    struct Config {
        u32 _0;
        gobj::MoveParamAccel _4;
    };

    StatePursuit(Boss* boss, Config config);
    virtual ~StatePursuit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    Config mConfig;
};

}
}
}
}

#endif
