#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEANGER_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEANGER_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateAnger : public StateBase {
public:
    StateAnger(Boss* boss);
    virtual ~StateAnger();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateColorFlash();
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mPhase;
    u32 mFlashCount;
    u32 mFlashFrame;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
