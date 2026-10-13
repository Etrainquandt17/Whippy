#ifndef SCN_STEP_ENEMY_BABUT_STATEFLYSINCURVE_H
#define SCN_STEP_ENEMY_BABUT_STATEFLYSINCURVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateFlySinCurve : public StateBase {
public:
    StateFlySinCurve(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    f32 difficultyRate() const;
    f32 freq() const;
    f32 speedX() const;

private:
    f32 mAngle;
    f32 mBaseY;
    f32 mSpeedX;
    u32 mFrame;
};

}
}
}
}

#endif
