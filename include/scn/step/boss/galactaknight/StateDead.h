#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEDEAD_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEDEAD_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateRotate();
    void stagingBossDead();
    bool _8;
    bool mIsFirst;
    bool mIsStaged;
    u32 mCount;
    u32 mFrame;
    f32 mRot;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsBound;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
