#ifndef SCN_STEP_WEAPON_ROAHOAR_STATEPURSUIT_H
#define SCN_STEP_WEAPON_ROAHOAR_STATEPURSUIT_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

// TODO: members and overrides; the unit is not written yet.
class StatePursuit : public StateBase {
public:
    StatePursuit(Weapon* weapon);
};

}}}}  // namespace scn::step::weapon::roahoar

#endif
