#ifndef SCN_STEP_BOSS_LOWPER_STATESPARKATTACKSTART_H
#define SCN_STEP_BOSS_LOWPER_STATESPARKATTACKSTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateSparkAttackStart : public StateBase {
public:
    StateSparkAttackStart(Boss* boss, u32 frame, u32 _3, f32 y, bool isRolling);
    virtual ~StateSparkAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    u32 _10;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsRolling;
};

}}}}  // namespace scn::step::boss::lowper

#endif
