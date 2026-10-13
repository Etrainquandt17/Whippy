#ifndef SCN_STEP_WEAPON_SUPERHAMMERQUAKE_UTILITY_H
#define SCN_STEP_WEAPON_SUPERHAMMERQUAKE_UTILITY_H

#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/superhammerquake/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace superhammerquake {

class Utility {
public:
    static const Param& GetParamCommon(Weapon& weapon);
    static const LevelParam& GetParamLevel(Weapon& weapon);
};

}
}
}
}

#endif
