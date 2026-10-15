#ifndef SCN_STEP_BOSS_GOLIATH_STATEDEADFALL_H
#define SCN_STEP_BOSS_GOLIATH_STATEDEADFALL_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateDeadFall : public StateBase {
public:
    StateDeadFall(Boss* boss);
    virtual ~StateDeadFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mMoveFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::goliath

#endif
