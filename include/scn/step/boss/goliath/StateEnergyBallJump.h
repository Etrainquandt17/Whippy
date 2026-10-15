#ifndef SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLJUMP_H
#define SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateEnergyBallJump : public StateBase {
public:
    StateEnergyBallJump(Boss* boss, u32 _1, u32 _2, f32 _3);
    virtual ~StateEnergyBallJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 _C;
    u32 _10;
    f32 _14;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::goliath

#endif
