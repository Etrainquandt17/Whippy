#ifndef SCN_STEP_HERO_NEEDLEPARAM_H
#define SCN_STEP_HERO_NEEDLEPARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members around these. Param::needle() returns it; the sub-structs are what the
// states' file-local param() functions return.
struct NeedleParamAttackUp {
    u32 _0;
    u32 _4;
};

struct NeedleParamBurnAttack {
    u32 _0;
    u32 _4;
};

struct NeedleParam {
    u32 _0[0xC];
    NeedleParamAttackUp _30;
    NeedleParamBurnAttack _38;
    u32 _40[0xA];
    gobj::MoveParamFall _68;
};

}
}
}

#endif
