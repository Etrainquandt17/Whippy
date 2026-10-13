#ifndef SCN_STEP_VACUUM_ATTACKER_H
#define SCN_STEP_VACUUM_ATTACKER_H

#include "scn/step/vacuum/AbilityType.h"
#include "types.h"

namespace scn {
namespace step {
namespace vacuum {

class Attacker {
public:
    u32 vacuumCount() const;
    void resetVacuumCount();
    void resetVacuumHold();
    void setHoldCannonBlowWait(u32 index);
    void setHoldCannonWait(u32 index);
    void resetVacuumReserve();
    u32 abilityCount(AbilityType type) const;
    int ability(AbilityType type, u32 index) const;
    void clearAbility();
    bool isEnfDrink() const;
    void onDrink();
};

}
}
}

#endif
