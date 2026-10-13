#ifndef SCN_STEP_WEAPON_BOMBBOMB_UTILITY_H
#define SCN_STEP_WEAPON_BOMBBOMB_UTILITY_H

#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

class Utility {
public:
    static bool IsSearchCollide(Weapon& weapon);
};

}}}}  // namespace scn::step::weapon::bombbomb

#endif
