#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHERO_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLJUMPFARHERO_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallJumpFarHero : public StateBase {
public:
    StateWallJumpFarHero(Boss* boss, f32 height, u32 time);
    virtual ~StateWallJumpFarHero();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mHeight;
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRot;
    f32 mRotSpeed;
};

}}}}  // namespace scn::step::boss::goliath

#endif
