#ifndef SCN_STEP_WEAPON_METASHOCKWAVE_PARAM_H
#define SCN_STEP_WEAPON_METASHOCKWAVE_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace metashockwave {

// TODO: name the members.
struct Param {
    gobj::MoveParamDecel _0;
    u32 _4;
    u32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
};

}
}
}
}

#endif
