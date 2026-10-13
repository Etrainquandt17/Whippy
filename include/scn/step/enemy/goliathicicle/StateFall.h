#ifndef SCN_STEP_ENEMY_GOLIATHICICLE_STATEFALL_H
#define SCN_STEP_ENEMY_GOLIATHICICLE_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathicicle {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy, f32 rot);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFall;
    f32 mFallAccel;
    f32 mRot;
    u32 mWaitFrame;
};

}}}}  // namespace scn::step::enemy::goliathicicle

#endif
