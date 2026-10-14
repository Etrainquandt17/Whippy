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
    enum State {
        STATE_NONE,
        STATE_REFLECT,
        STATE_NORMAL,
        STATE_TACKLE,
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

}}}}  // namespace scn::step::boss::roah

#endif
