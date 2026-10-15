#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKETATTACK_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKETATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateRocketAttack : public StateBase {
public:
    StateRocketAttack(Boss* boss, f32 x, u32 time, bool isLast);
    virtual ~StateRocketAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsLast;
};

}}}}  // namespace scn::step::boss::goliath

#endif
