#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEVERTICALSHOTFOLLOW_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEVERTICALSHOTFOLLOW_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateVerticalShotFollow : public StateBase {
public:
    StateVerticalShotFollow(Enemy* enemy);
    virtual ~StateVerticalShotFollow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mOffset;
    hel::math::Vector3 mVelocity;
};

}
}
}
}

#endif
