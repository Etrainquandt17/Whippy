#ifndef SCN_STEP_BOSS_GOLIATH_STATEANGER_H
#define SCN_STEP_BOSS_GOLIATH_STATEANGER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateAnger : public StateBase {
public:
    StateAnger(Boss* boss);
    virtual ~StateAnger();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mZoomHandle;
};

}}}}  // namespace scn::step::boss::goliath

#endif
