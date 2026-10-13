#ifndef SCN_STEP_WEAPON_DEESPEAR_UTILITY_H
#define SCN_STEP_WEAPON_DEESPEAR_UTILITY_H

#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

class Utility {
public:
    static void Rotate(Weapon& weapon);
    static void Vanish(Weapon& weapon);
};

}}}}  // namespace scn::step::weapon::deespear

#endif
