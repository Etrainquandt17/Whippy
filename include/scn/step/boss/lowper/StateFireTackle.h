#ifndef SCN_STEP_BOSS_LOWPER_STATEFIRETACKLE_H
#define SCN_STEP_BOSS_LOWPER_STATEFIRETACKLE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFireTackle : public StateBase {
public:
    StateFireTackle(Boss* boss, u32 frame, bool isEx);
    virtual ~StateFireTackle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    f32 mRotY;
    bool mIsEx;
};

}}}}  // namespace scn::step::boss::lowper

#endif
