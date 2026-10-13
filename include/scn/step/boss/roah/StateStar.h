#ifndef SCN_STEP_BOSS_ROAH_STATESTAR_H
#define SCN_STEP_BOSS_ROAH_STATESTAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateStar : public StateBase {
public:
    struct Config {
        int _0;
    };

    StateStar(Boss* boss, Config config);
    virtual ~StateStar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
