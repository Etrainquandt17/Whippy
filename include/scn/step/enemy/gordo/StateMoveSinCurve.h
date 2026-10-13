#ifndef SCN_STEP_ENEMY_GORDO_STATEMOVESINCURVE_H
#define SCN_STEP_ENEMY_GORDO_STATEMOVESINCURVE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gordo {

class StateMoveSinCurve : public StateBase {
public:
    StateMoveSinCurve(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mBase;
    f32 mAngle;
};

}
}
}
}

#endif
