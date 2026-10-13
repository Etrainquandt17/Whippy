#ifndef SCN_STEP_ENEMY_PLUID_STATEJUMP_H
#define SCN_STEP_ENEMY_PLUID_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pluid {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsStart;
    bool mIsJumped;
    bool mIsRight;
    u32 mFrame;
    f32 mSpeedH;
    f32 mSpeedV;
};

}
}
}
}

#endif
