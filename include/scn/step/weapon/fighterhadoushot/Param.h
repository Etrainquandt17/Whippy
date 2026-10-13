#ifndef SCN_STEP_WEAPON_FIGHTERHADOUSHOT_PARAM_H
#define SCN_STEP_WEAPON_FIGHTERHADOUSHOT_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

// TODO: name the members.
struct ShotParam {
    f32 _0;
    f32 _4;
};

struct ExplosionParam {
    f32 _0;
    u32 _4;
};

struct Param {
    ShotParam _0;
    ShotParam _8;
    ExplosionParam _10;
    ShotParam _18;
    ExplosionParam _20;
};

}
}
}
}

#endif
