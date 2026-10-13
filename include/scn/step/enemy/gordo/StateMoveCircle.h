#ifndef SCN_STEP_ENEMY_GORDO_STATEMOVECIRCLE_H
#define SCN_STEP_ENEMY_GORDO_STATEMOVECIRCLE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gordo {

class StateMoveCircle : public StateBase {
public:
    StateMoveCircle(Enemy* enemy);
    virtual void procMove();

private:
    hel::math::Vector3 mCenter;
    f32 mAngle;
    f32 mRadius;
    f32 mSpeed;
};

}
}
}
}

#endif
