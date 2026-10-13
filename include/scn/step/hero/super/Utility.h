#ifndef SCN_STEP_HERO_SUPER_UTILITY_H
#define SCN_STEP_HERO_SUPER_UTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

struct SuperParamAbility;
class Hero;
namespace super {

class Utility {
public:
    static void OnSuperActionStart(Hero& hero);
    static void OnSuperActionEnd(Hero& hero);
    static void SetRenderFore(Hero& hero);
    static void UnsetRenderFore(Hero& hero);
    static void InitFuel(Hero& hero);
    static void SuperUseFuel(Hero& hero);
    static void SuperLeakFuel(Hero& hero);
    static u32 CalcSuperLeakFuel(Hero& hero);
    static void UnlinkPiggyBack(Hero& hero);
    static const SuperParamAbility& Param(Hero& hero);
    static void OnShowHero(Hero& hero);
    static void OnHideHero(Hero& hero);
};

}
}
}
}

#endif
