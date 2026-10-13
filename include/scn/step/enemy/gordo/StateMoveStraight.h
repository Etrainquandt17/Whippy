#ifndef SCN_STEP_ENEMY_GORDO_STATEMOVESTRAIGHT_H
#define SCN_STEP_ENEMY_GORDO_STATEMOVESTRAIGHT_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gordo {

class StateMoveStraight : public StateBase {
public:
    StateMoveStraight(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mDir;
    f32 mBaseX;
};

}
}
}
}

#endif
