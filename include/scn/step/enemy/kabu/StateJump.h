#ifndef SCN_STEP_ENEMY_KABU_STATEJUMP_H
#define SCN_STEP_ENEMY_KABU_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace kabu {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void setSpeed();

private:
    u32 mFrame;
    bool mIsRight;
    f32 mSpeedH;
};

}
}
}
}

#endif
