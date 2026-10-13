#ifndef SCN_STEP_ENEMY_DOUBTERSNAKE_STATEESCAPENEAR_H
#define SCN_STEP_ENEMY_DOUBTERSNAKE_STATEESCAPENEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace doubtersnake {

class StateEscapeNear : public StateBase {
public:
    StateEscapeNear(Enemy* enemy);
    virtual ~StateEscapeNear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mStartY;
    f32 mAngle;
    bool mIsJump;
};

}
}
}
}

#endif
