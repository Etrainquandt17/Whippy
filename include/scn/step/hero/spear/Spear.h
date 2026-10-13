#ifndef SCN_STEP_HERO_SPEAR_SPEAR_H
#define SCN_STEP_HERO_SPEAR_SPEAR_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spear {

class Spear : public AbilityBase {
public:
    Spear(Component& component, Hero& hero);
    virtual ~Spear();

private:
    u32 _C;
};

}
}
}
}

#endif
