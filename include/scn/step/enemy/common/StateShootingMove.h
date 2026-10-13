#ifndef SCN_STEP_ENEMY_COMMON_STATESHOOTINGMOVE_H
#define SCN_STEP_ENEMY_COMMON_STATESHOOTINGMOVE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateShootingMove : public StateBase {
public:
    struct Config {
        f32 _0;
        f32 _4;
    };

    StateShootingMove(Enemy* enemy, Config config);
    virtual ~StateShootingMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mCenterX;
    hel::math::Vector3 mVelocity;
};

}
}
}
}

#endif
