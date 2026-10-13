#ifndef SCN_STEP_WEAPON_METALGENERALBITSHOT_PARAM_H
#define SCN_STEP_WEAPON_METALGENERALBITSHOT_PARAM_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralbitshot {

// TODO: name the members.
struct VariationParam {
    f32 _0;
    f32 _4;
    u32 _8;
    gobj::MoveParamAccel _C;
};

struct Param {
    VariationParam _0;
    VariationParam _18;
};

}}}}  // namespace scn::step::weapon::metalgeneralbitshot

#endif
