#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEGUARD_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEGUARD_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateGuard : public StateBase {
public:
    StateGuard(Boss* boss, f32 distance, u32 frame, u32 guardFrame);
    virtual ~StateGuard();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
    u32 mCount;
    u32 mGuardFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
