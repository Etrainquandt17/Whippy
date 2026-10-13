#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEHEALCHARGESTART_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEHEALCHARGESTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateHealChargeStart : public IState {
public:
    StateHealChargeStart(Boss* boss);
    virtual ~StateHealChargeStart();
};

}

}}}  // namespace scn::step::boss

#endif
