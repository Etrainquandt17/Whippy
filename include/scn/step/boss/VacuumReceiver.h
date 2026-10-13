#ifndef SCN_STEP_BOSS_VACUUMRECEIVER_H
#define SCN_STEP_BOSS_VACUUMRECEIVER_H

#include "hel/math/Vector2.h"
#include "scn/step/hero/AbilityKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

// TODO: members and the base class.
class VacuumReceiver {
public:
    void setAbilityKind(hero::AbilityKind kind);
    hero::AbilityKind abilityKind() const;
    void setIsValid(bool isValid);
    void setIsResist(bool isResist);
    void setEndVacuumed();
    void onDead();
    void reqDeadEnf();
    hel::math::Vector2 getAttackerPos() const;
};

}}}  // namespace scn::step::boss

#endif
