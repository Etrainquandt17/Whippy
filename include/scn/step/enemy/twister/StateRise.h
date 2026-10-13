#ifndef SCN_STEP_ENEMY_TWISTER_STATERISE_H
#define SCN_STEP_ENEMY_TWISTER_STATERISE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace twister {

class StateRise : public StateBase {
public:
    StateRise(Enemy* enemy);
    virtual ~StateRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsRising;
    u32 mFrame;
    f32 mSpeedV;
    bool mIsJump;
    f32 mThetaSpeed;
};

}
}
}
}

#endif
