#ifndef SCN_STEP_BOSS_KINGSDOO_STATECHARGEATTACKSTART_H
#define SCN_STEP_BOSS_KINGSDOO_STATECHARGEATTACKSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

class StateChargeAttackStart : public StateBase {
public:
    StateChargeAttackStart(Boss* boss);
    virtual ~StateChargeAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
