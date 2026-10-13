#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATESHUTTLELOOP_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATESHUTTLELOOP_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateShuttleLoop : public StateBase {
public:
    StateShuttleLoop(Boss* boss, bool isAttack);
    virtual ~StateShuttleLoop();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
