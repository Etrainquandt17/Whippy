#ifndef SCN_STEP_WEAPON_METABEAM_PARAM_H
#define SCN_STEP_WEAPON_METABEAM_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace metabeam {

// TODO: name the members.
struct Param {
    u32 _0;
    f32 _4;
    f32 _8;
    gobj::MoveParamDecel _C;
};

}
}
}
}

#endif
