#ifndef SCN_STEP_HERO_CLEARDANCEUTIL_H
#define SCN_STEP_HERO_CLEARDANCEUTIL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

class ClearDanceUtil {
public:
    static u32 ResetZoom(Hero& hero, u32);
    static u32 SetZoom(Hero& hero);
};

}
}
}

#endif
