#ifndef SCN_STEP_ENEMY_KABU_STATEMOVEAROUND_H
#define SCN_STEP_ENEMY_KABU_STATEMOVEAROUND_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace kabu {

class StateMoveAround : public StateBase {
public:
    StateMoveAround(Enemy* enemy);
    virtual ~StateMoveAround();
    virtual void procMove();
    virtual void procFixPos();

    void turn();

private:
    gobj::MoveParamAccel mAccel;
    f32 mCenterX;
    u32 mTurnFrame;
    bool mIsTurning;
};

}
}
}
}

#endif
