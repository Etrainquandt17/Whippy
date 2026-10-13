#ifndef SCN_STEP_ENEMY_GIGATZO_STATEAIM_H
#define SCN_STEP_ENEMY_GIGATZO_STATEAIM_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gigatzo {

class StateAim : public StateBase {
public:
    StateAim(Enemy* enemy);
    virtual ~StateAim();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 roundAngle(f32 angle);
    
    u32 mFrame;
    u32 mFrame2;
    u32 mFrame3;
    f32 mStartAngle;
    f32 mMidAngle;
    f32 mEndAngle;
    f32 mAngle;
};

}
}
}
}

#endif
