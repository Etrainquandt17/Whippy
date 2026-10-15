#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLWAIT_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLWAIT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallWait : public StateBase {
public:
    StateWallWait(Boss* boss);
    virtual ~StateWallWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
