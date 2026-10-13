#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEJUMPEND_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEJUMPEND_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateJumpEnd : public StateBase {
public:
    StateJumpEnd(Boss* boss, ScriptKind kind, f32 distance, u32 frame);
    virtual ~StateJumpEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
