#ifndef SCN_STEP_BOSS_HRD3_COLLISIONCTRL_H
#define SCN_STEP_BOSS_HRD3_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

}
class Boss;
namespace hrd3 {

// TODO: members; the return types are guesses.
class CollisionCtrl {
public:
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7
    };

    struct CollisionData;

    CollisionCtrl(Boss& boss);
    ~CollisionCtrl();

    void update();
    void setState(State state);
    void setResetCollisionForce();
    bool checkOnLine(f32 a, f32 b) const;
    void setCollision();
    void addCollision(const CollisionData& data);
    void setAttackType();
    void setResistLv();
    void onStateChange();
};

}
}
}
}

#endif
