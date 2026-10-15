#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLCLIMB_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLCLIMB_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallClimb : public StateBase {
public:
    StateWallClimb(Boss* boss, f32 height, u32 time);
    virtual ~StateWallClimb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::goliath

#endif
