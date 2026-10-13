#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATESPINATTACKCHARGE_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATESPINATTACKCHARGE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateSpinAttackCharge : public StateBase {
public:
    StateSpinAttackCharge(Boss* boss, u32 frame, f32 distance, u32 count);
    virtual ~StateSpinAttackCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsStart;
    f32 mDistance;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
