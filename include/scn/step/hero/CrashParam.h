#ifndef SCN_STEP_HERO_CRASHPARAM_H
#define SCN_STEP_HERO_CRASHPARAM_H

#include "gobj/MoveParam.h"
#include "scn/step/hero/ShakeChargeEnv.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind 0x24. Param::crash() returns it.
struct CrashParam {
    gobj::MoveParamDecel _0;
    gobj::MoveParamDecel _4;
    gobj::MoveParamFall _8;
    ShakeChargeEnv _14;
};

}
}
}

#endif
