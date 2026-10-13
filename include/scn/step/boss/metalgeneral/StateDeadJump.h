#ifndef SCN_STEP_BOSS_METALGENERAL_STATEDEADJUMP_H
#define SCN_STEP_BOSS_METALGENERAL_STATEDEADJUMP_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StateDeadJump : public StateBase {
public:
    StateDeadJump(Boss* boss);
    virtual ~StateDeadJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
