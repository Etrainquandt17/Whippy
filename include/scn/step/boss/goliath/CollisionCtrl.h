#ifndef SCN_STEP_BOSS_GOLIATH_COLLISIONCTRL_H
#define SCN_STEP_BOSS_GOLIATH_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class CollisionCtrl {
public:
    enum State {
        STATE_NONE,
        STATE_NORMAL,
        STATE_PUNCH,
        STATE_REFLECT,
    };

    CollisionCtrl(Boss& boss);

    void onStateChange();
    void setState(State state);

private:
    void setCollision();
    void setResistLv();

    Boss& mBoss;
    State mState;
};

}}}}  // namespace scn::step::boss::goliath

#endif
