#ifndef SCN_STEP_ENEMY_GOLIATHICICLE_STATEFLYWAIT_H
#define SCN_STEP_ENEMY_GOLIATHICICLE_STATEFLYWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathicicle {

class StateFlyWait : public StateBase {
public:
    StateFlyWait(Enemy* enemy);
    virtual ~StateFlyWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}}}}  // namespace scn::step::enemy::goliathicicle

#endif
