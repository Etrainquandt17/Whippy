#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPHOLD_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPHOLD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpHold : public StateBase {
public:
    StateEtherJumpHold(Boss* boss, u32 frame);
    virtual ~StateEtherJumpHold();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    f32 mStartX;
    f32 mGoalX;
};

}}}}  // namespace scn::step::boss::doubter

#endif
