#ifndef SCN_STEP_BOSS_HRD3_STATEPRESSFALL_H
#define SCN_STEP_BOSS_HRD3_STATEPRESSFALL_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StatePressFall : public StateBase {
public:
    StatePressFall(Boss* boss, u32 boundCount);
    virtual ~StatePressFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    u32 mBoundCount;
    hel::math::Vector3 mStartPos;
    f32 mGoalY;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
