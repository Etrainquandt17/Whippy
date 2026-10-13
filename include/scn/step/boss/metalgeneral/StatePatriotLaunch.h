#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTLAUNCH_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTLAUNCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StatePatriotLaunch : public StateBase {
public:
    StatePatriotLaunch(Boss* boss);
    virtual ~StatePatriotLaunch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsSignaled;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
