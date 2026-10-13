#ifndef SCN_STEP_ENEMY_GOLIATHICEBALL_STATEROLLINGFALL_H
#define SCN_STEP_ENEMY_GOLIATHICEBALL_STATEROLLINGFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathiceball {

class StateRollingFall : public StateBase {
public:
    StateRollingFall(Enemy* enemy);
    virtual ~StateRollingFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}}}}  // namespace scn::step::enemy::goliathiceball

#endif
