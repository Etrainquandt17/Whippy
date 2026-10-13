#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHOMINGFOLLOW_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHOMINGFOLLOW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateHomingFollow : public StateBase {
public:
    StateHomingFollow(Enemy* enemy);
    virtual ~StateHomingFollow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    f32 mAngle;
    f32 mRadius;
};

}
}
}
}

#endif
