#ifndef SCN_STEP_BOSS_LOWPER_COLLISIONCTRL_H
#define SCN_STEP_BOSS_LOWPER_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

struct CollParam;

class CollisionCtrl {
public:
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5
    };

    CollisionCtrl(Boss& boss);
    ~CollisionCtrl();

    void update();
    void setState(State state);
    void setCollision();
    void setHit();
    void setAttack();
    const CollParam* param();
    void setAttackType();

private:
    Boss& mBoss;
    State mState;
    bool mIsAttack;
    bool mIsHit;
};

}}}}  // namespace scn::step::boss::lowper

#endif
