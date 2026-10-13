#ifndef SCN_STEP_BOSS_ROAH_STATEZPASSTHROUGH_H
#define SCN_STEP_BOSS_ROAH_STATEZPASSTHROUGH_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateZPassThrough : public StateBase {
public:
    StateZPassThrough(Boss* boss);
    virtual ~StateZPassThrough();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::roah

#endif
