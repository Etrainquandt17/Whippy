#ifndef SCN_STEP_HERO_SPARKPARAM_H
#define SCN_STEP_HERO_SPARKPARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind these. Param::spark() returns it.
struct SparkParamAttack {
    u32 _0;
    u32 _4;
    u32 _8;
};

struct SparkParamAttackOver {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
};

struct SparkParam {
    SparkParamAttack _0;
    SparkParamAttackOver _C;
};

}
}
}

#endif
