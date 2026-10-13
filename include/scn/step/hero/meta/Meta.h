#ifndef SCN_STEP_HERO_META_META_H
#define SCN_STEP_HERO_META_META_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace meta {

class Meta : public AbilityBase {
public:
    Meta(Component& component, Hero& hero);
    virtual ~Meta();

private:
    u32 _C[(0x18 - 0xC) / 4];
};

}
}
}
}

#endif
