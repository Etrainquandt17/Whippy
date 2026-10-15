#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKETCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKETCHARGE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateRocketCharge : public StateBase {
public:
    StateRocketCharge(Boss* boss);
    virtual ~StateRocketCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
