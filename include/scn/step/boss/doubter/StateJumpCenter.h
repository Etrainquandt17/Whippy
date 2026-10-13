#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUMPCENTER_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUMPCENTER_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJumpCenter : public StateBase {
public:
    StateJumpCenter(Boss* boss, f32 height, u32 frame);
    virtual ~StateJumpCenter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mHeight;
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::doubter

#endif
