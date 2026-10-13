#ifndef SCN_STEP_HERO_NINJA_CUSTOM_H
#define SCN_STEP_HERO_NINJA_CUSTOM_H

#include "scn/step/hero/AbilityCustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace ninja {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual ~Custom();

private:
    u32 _8[(0x44 - 0x8) / 4];
};

}
}
}
}

#endif
