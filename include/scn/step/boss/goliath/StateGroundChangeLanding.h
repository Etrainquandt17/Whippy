#ifndef SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGELANDING_H
#define SCN_STEP_BOSS_GOLIATH_STATEGROUNDCHANGELANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateGroundChangeLanding : public StateBase {
public:
    StateGroundChangeLanding(Boss* boss);
    virtual ~StateGroundChangeLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
