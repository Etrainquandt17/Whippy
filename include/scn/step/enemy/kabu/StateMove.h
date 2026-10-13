#ifndef SCN_STEP_ENEMY_KABU_STATEMOVE_H
#define SCN_STEP_ENEMY_KABU_STATEMOVE_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace kabu {

class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual ~StateMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    gobj::MoveParamAccel mAccel;
    u32 mFrame;
    u32 mTurnFrame;
    u32 mJumpFrame;
    bool mIsCliffTurn;
    bool mIsTurning;
};

}}}}  // namespace scn::step::enemy::kabu

#endif
