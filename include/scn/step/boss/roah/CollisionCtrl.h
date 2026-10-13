#ifndef SCN_STEP_BOSS_ROAH_COLLISIONCTRL_H
#define SCN_STEP_BOSS_ROAH_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

struct CollParam;

}

class Boss;

namespace roah {

class CollisionCtrl {
public:
    // TODO: the names of the enumerators.
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
    };

    CollisionCtrl(Boss& boss);
    ~CollisionCtrl();

    void update();
    void setState(State state);

private:
    void setHit();
    const CollParam* param();
    void setAttackType();
    void setResistLv();

    Boss& mBoss;
    State mState;
    bool mIsHit;
};

}
}
}
}

#endif
