#ifndef SCN_STEP_BOSS_LOWPER_STATEMOVE_H
#define SCN_STEP_BOSS_LOWPER_STATEMOVE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateMove : public StateBase {
public:
    StateMove(Boss* boss, const hel::math::Vector3& pos, u32 frame);
    virtual ~StateMove();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mCount;
    u32 mFrame;
};

}}}}  // namespace scn::step::boss::lowper

#endif
