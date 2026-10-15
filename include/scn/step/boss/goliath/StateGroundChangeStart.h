#ifndef SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGESTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGESTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateGroundChangeStart : public StateBase {
public:
    StateGroundChangeStart(Boss* boss);
    virtual ~StateGroundChangeStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
