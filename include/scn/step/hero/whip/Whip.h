#ifndef SCN_STEP_HERO_WHIP_WHIP_H
#define SCN_STEP_HERO_WHIP_WHIP_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace whip {

class Whip : public AbilityBase {
public:
    Whip(Component& component, Hero& hero);
    virtual ~Whip();

private:
    u32 _C[(0x40 - 0xC) / 4];
};

}
}
}
}

#endif
