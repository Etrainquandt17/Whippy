#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEUNDERTHRUST_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEUNDERTHRUST_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateUnderThrust : public StateBase {
public:
    StateUnderThrust(Boss* boss);
    virtual ~StateUnderThrust();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void changeStateLanding();
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsStart;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
