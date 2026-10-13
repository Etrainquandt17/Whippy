#include "scn/step/weapon/superhammerquake/Utility.h"

#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace superhammerquake {

const Param& Utility::GetParamCommon(Weapon& weapon) {
    return weapon.param().superHammerQuake();
}

const LevelParam& Utility::GetParamLevel(Weapon& weapon) {
    switch (weapon.variation()) {
    case 0:
        return weapon.param().superHammerQuake()._8;
    case 1:
        return weapon.param().superHammerQuake()._2C;
    case 2:
        return weapon.param().superHammerQuake()._50;
    default:
        return weapon.param().superHammerQuake()._8;
    }
}

}}}}  // namespace scn::step::weapon::superhammerquake
