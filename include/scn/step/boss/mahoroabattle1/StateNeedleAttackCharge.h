#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACKCHARGE_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATENEEDLEATTACKCHARGE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateNeedleAttackCharge : public IState {
public:
    StateNeedleAttackCharge(Boss* boss);
    virtual ~StateNeedleAttackCharge();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
