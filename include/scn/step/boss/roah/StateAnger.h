#ifndef SCN_STEP_BOSS_ROAH_STATEANGER_H
#define SCN_STEP_BOSS_ROAH_STATEANGER_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateAnger : public StateBase {
public:
    StateAnger(Boss* boss);
    virtual ~StateAnger();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mGoalPos;
};

}}}}  // namespace scn::step::boss::roah

#endif
