#ifndef SCN_STEP_ENEMY_FATTYBUFFERJR_STATEJUMP_H
#define SCN_STEP_ENEMY_FATTYBUFFERJR_STATEJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace fattybufferjr {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy, const hel::math::Vector3& velocity);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
