#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLEUPPER_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLEUPPER_H

#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StatePatriotTackleUpper : public StateBase {
public:
    StatePatriotTackleUpper(Boss* boss, hel::math::Direction3 dir);
    virtual ~StatePatriotTackleUpper();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mWaitCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    hel::math::Direction3 mDir;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
