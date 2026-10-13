#ifndef SCN_STEP_BOSS_LOWPER_STATESPARKSHOT_H
#define SCN_STEP_BOSS_LOWPER_STATESPARKSHOT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSparkShot : public StateBase {
public:
    StateSparkShot(Boss* boss);
    virtual ~StateSparkShot();
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
