#ifndef SCN_STEP_HERO_SUPERSWORDPARAM_H
#define SCN_STEP_HERO_SUPERSWORDPARAM_H

#include "scn/step/hero/modeldesc/Dynamics.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind these. Param::superSword() returns it.
struct SuperSwordParam {
    f32 _0;
    modeldesc::Dynamics::NodeParam _4[4];
};

}
}
}

#endif
