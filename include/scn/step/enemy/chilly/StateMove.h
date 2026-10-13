#ifndef SCN_STEP_ENEMY_CHILLY_STATEMOVE_H
#define SCN_STEP_ENEMY_CHILLY_STATEMOVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace chilly {

class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mTurnWait;
};

}}}}  // namespace scn::step::enemy::chilly

#endif
