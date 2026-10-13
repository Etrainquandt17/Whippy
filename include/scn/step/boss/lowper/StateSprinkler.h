#ifndef SCN_STEP_BOSS_LOWPER_STATESPRINKLER_H
#define SCN_STEP_BOSS_LOWPER_STATESPRINKLER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSprinkler : public StateBase {
public:
    StateSprinkler(Boss* boss);
    virtual ~StateSprinkler();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBullet();
};

}
}
}
}

#endif
