#ifndef SCN_STEP_HERO_DEE_DEE_H
#define SCN_STEP_HERO_DEE_DEE_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace dee {

class Dee : public AbilityBase {
public:
    Dee(Component& component, Hero& hero);
    virtual ~Dee();

private:
    u32 _C;
};

}
}
}
}

#endif
