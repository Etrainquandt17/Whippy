#ifndef SCN_STEP_HERO_RIDE_UTILITY_H
#define SCN_STEP_HERO_RIDE_UTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace ride {

class Utility {
public:
    static bool TryToDropOffStepShoe(Hero& hero);
    static bool TryToEnterDoorStepShoe(Hero& hero);
    static bool IsJumpInput(Hero& hero, u32 frame);
};

}
}
}
}

#endif
