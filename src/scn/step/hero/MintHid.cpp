#include "scn/step/hero/MintHid.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/Hid.h"

namespace scn {
namespace step {
namespace hero {

namespace {

Hid& t_obj() {
    return MintHero::Obj().hid();
}

}

namespace MintHid {

bool IsHold(u32 mask) {
    return t_obj().isHold(mask);
}

bool IsTrigger(u32 mask) {
    return t_obj().isTrigger(mask);
}

void SetAutoInputHold(u32 mask) {
    t_obj().setAutoInputHold(mask);
}

}
}
}
}
