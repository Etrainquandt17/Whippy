#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLJUMP_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLJUMP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallJump : public StateBase {
public:
    StateWallJump(Boss* boss, f32 height, u32 time);
    virtual ~StateWallJump();
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
