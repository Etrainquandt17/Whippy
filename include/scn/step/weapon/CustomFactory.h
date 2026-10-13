#ifndef SCN_STEP_WEAPON_CUSTOMFACTORY_H
#define SCN_STEP_WEAPON_CUSTOMFACTORY_H

#include "mem/ExplicitScopedPtr.h"
#include "scn/step/weapon/ICustom.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class CustomFactory {
public:
    static void Create(Weapon& weapon, mem::ExplicitScopedPtr<ICustom>& custom);
};

}}}  // namespace scn::step::weapon

#endif
