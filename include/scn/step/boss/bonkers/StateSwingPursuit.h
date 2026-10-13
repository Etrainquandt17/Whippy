#ifndef SCN_STEP_BOSS_BONKERS_STATESWINGPURSUIT_H
#define SCN_STEP_BOSS_BONKERS_STATESWINGPURSUIT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateSwingPursuit : public StateBase {
public:
    StateSwingPursuit(Boss* boss);
    virtual ~StateSwingPursuit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsMove;
    u32 mTurnWait;
    u32 mCount;
    bool mIsRight;
};

}}}}  // namespace scn::step::boss::bonkers

#endif
