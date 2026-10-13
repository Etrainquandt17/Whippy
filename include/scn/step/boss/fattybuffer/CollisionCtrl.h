#ifndef SCN_STEP_BOSS_FATTYBUFFER_COLLISIONCTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

// TODO: the member at 8 and the private functions (param, paramIntpFrom, setCollision, setCollisionNode, setAttackType, setResistLv).
class CollisionCtrl {
public:
    // TODO: name the states.
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7,
        STATE_8,
        STATE_9,
        STATE_10,
        STATE_11,
        STATE_12,
        STATE_13,
        STATE_14,
        STATE_15,
    };

    CollisionCtrl(Boss& boss);
    ~CollisionCtrl();
    void setState(State state);
    void update();

private:
    Boss& mBoss;
    State mState;
    u32 _8;
};

}
}
}
}

#endif
