#ifndef SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHERO_H
#define SCN_STEP_BOSS_GOLIATH_STATEJUMPFARHERO_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateJumpFarHero : public StateBase {
public:
    StateJumpFarHero(Boss* boss, u32 time, f32 distance);
    virtual ~StateJumpFarHero();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRot;
    f32 mRotSpeed;
};

}}}}  // namespace scn::step::boss::goliath

#endif
