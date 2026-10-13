#ifndef SCN_STEP_BOSS_ROAH_STATEMAHOROAMOTIONSTARWAIT_H
#define SCN_STEP_BOSS_ROAH_STATEMAHOROAMOTIONSTARWAIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateMahoroaMotionStarWait : public StateBase {
public:
    StateMahoroaMotionStarWait(Boss* boss);
    virtual ~StateMahoroaMotionStarWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
