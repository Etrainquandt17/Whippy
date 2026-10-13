#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_COLLISIONCTRL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}
class Boss;
namespace galactaknight {

struct CollParam;

class CollisionCtrl {
public:
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3
    };

    CollisionCtrl(Boss& boss);
    ~CollisionCtrl();

    void update();
    void onStateChange();
    void setState(State state);
    void setCollision();
    void setHit();
    void setAttack();
    const CollParam* param();
    void setAttackType();
    void setResistLv();

private:
    Boss& mBoss;
    State mState;
    bool mIsAttack;
    bool mIsHit;
};

}
}
}
}

#endif
