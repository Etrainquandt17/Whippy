#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATENWAYSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATENWAYSHOT_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

class StateNWayShot : public StateBase {
public:
    StateNWayShot(Enemy* enemy, const hel::math::Vector3& dir);
    virtual ~StateNWayShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mDir;
};

}
}
}
}

#endif
