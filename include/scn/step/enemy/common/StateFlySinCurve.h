#ifndef SCN_STEP_ENEMY_COMMON_STATEFLYSINCURVE_H
#define SCN_STEP_ENEMY_COMMON_STATEFLYSINCURVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateFlySinCurve : public StateBase {
public:
    StateFlySinCurve(Enemy* enemy);
    virtual ~StateFlySinCurve();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mAngle;
    f32 mBaseY;
    f32 mSpeedX;
};

}
}
}
}

#endif
