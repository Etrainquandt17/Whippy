#ifndef SCN_STEP_HERO_PARASOL_BARRIER_H
#define SCN_STEP_HERO_PARASOL_BARRIER_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
namespace parasol {

struct ParamBarrier;

class Barrier {
public:
    static void SetValid(Hero& hero, bool isValid);
    static void AddAttack(Hero& hero, bool);
    static void AddAttackNode(Hero& hero, bool, const ParamBarrier& param);
};

}
}
}
}

#endif
