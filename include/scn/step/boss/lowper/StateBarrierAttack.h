#ifndef SCN_STEP_BOSS_LOWPER_STATEBARRIERATTACK_H
#define SCN_STEP_BOSS_LOWPER_STATEBARRIERATTACK_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateBarrierAttack : public StateBase {
public:
    StateBarrierAttack(Boss* boss);
    virtual ~StateBarrierAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsStarted;
};

}}}}  // namespace scn::step::boss::lowper

#endif
