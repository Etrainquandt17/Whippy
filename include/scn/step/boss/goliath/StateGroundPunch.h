#ifndef SCN_STEP_BOSS_GOLIATH_STATEGROUNDPUNCH_H
#define SCN_STEP_BOSS_GOLIATH_STATEGROUNDPUNCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateGroundPunch : public StateBase {
public:
    StateGroundPunch(Boss* boss);
    virtual ~StateGroundPunch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
