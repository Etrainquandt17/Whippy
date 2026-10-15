#ifndef SCN_STEP_BOSS_GOLIATH_STATEDEADEND_H
#define SCN_STEP_BOSS_GOLIATH_STATEDEADEND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateDeadEnd : public StateBase {
public:
    StateDeadEnd(Boss* boss);
    virtual ~StateDeadEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::boss::goliath

#endif
