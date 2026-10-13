#ifndef SCN_STEP_HERO_SUPERBEAMPARAM_H
#define SCN_STEP_HERO_SUPERBEAMPARAM_H

#include "scn/step/hero/modeldesc/Dynamics.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: names and the members behind these. Param::superBeam() returns it.
struct SuperBeamParam {
    f32 _0;
    modeldesc::Dynamics::NodeParam _4[5];
};

}}}  // namespace scn::step::hero

#endif
