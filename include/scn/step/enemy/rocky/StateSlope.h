#ifndef SCN_STEP_ENEMY_ROCKY_STATESLOPE_H
#define SCN_STEP_ENEMY_ROCKY_STATESLOPE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateSlope : public StateBase {
public:
    StateSlope(Enemy* enemy);
    virtual ~StateSlope();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mNormalX;
};

}
}
}
}

#endif
