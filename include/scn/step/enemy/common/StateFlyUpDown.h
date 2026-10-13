#ifndef SCN_STEP_ENEMY_COMMON_STATEFLYUPDOWN_H
#define SCN_STEP_ENEMY_COMMON_STATEFLYUPDOWN_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateFlyUpDown : public StateBase {
public:
    StateFlyUpDown(Enemy* enemy);
    virtual ~StateFlyUpDown();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mAngle;
    f32 mBaseY;
};

}
}
}
}

#endif
