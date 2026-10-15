#ifndef SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGE_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateGroundChange : public StateBase {
public:
    StateGroundChange(Boss* boss);
    virtual ~StateGroundChange();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mLevel;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mFrame;
};

}}}}  // namespace scn::step::boss::goliath

#endif
