#ifndef SCN_STEP_BOSS_GOLIATH_STATEDEADSMASH_H
#define SCN_STEP_BOSS_GOLIATH_STATEDEADSMASH_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateDeadSmash : public StateBase {
public:
    StateDeadSmash(Boss* boss);
    virtual ~StateDeadSmash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void stagingBossDead();

    bool mIsPanelShown;
    bool mIsStaged;
    bool mIsSmash;
    u32 mTime;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRot;
    f32 mRotSpeed;
};

}}}}  // namespace scn::step::boss::goliath

#endif
