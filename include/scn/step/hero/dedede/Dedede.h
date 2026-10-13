#ifndef SCN_STEP_HERO_DEDEDE_DEDEDE_H
#define SCN_STEP_HERO_DEDEDE_DEDEDE_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace dedede {

class Dedede : public AbilityBase {
public:
    Dedede(Component& component, Hero& hero);
    virtual ~Dedede();

private:
    u32 _C;
};

}
}
}
}

#endif
