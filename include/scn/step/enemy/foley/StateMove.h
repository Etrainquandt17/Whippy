#ifndef SCN_STEP_ENEMY_FOLEY_STATEMOVE_H
#define SCN_STEP_ENEMY_FOLEY_STATEMOVE_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace foley {

class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual ~StateMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    gobj::MoveParamAccel mAccel;
    bool mIsReady;
};

}}}}  // namespace scn::step::enemy::foley

#endif
