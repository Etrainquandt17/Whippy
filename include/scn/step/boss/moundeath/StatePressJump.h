#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEPRESSJUMP_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEPRESSJUMP_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StatePressJump : public StateBase {
public:
    StatePressJump(Boss* boss, JumpKind kind);
    virtual ~StatePressJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    u32 mRotNum;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
    f32 mRot;
    f32 mRotDiff;
    JumpKind mKind;
};

}
}
}
}

#endif
