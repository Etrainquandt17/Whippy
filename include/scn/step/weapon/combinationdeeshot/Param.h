#ifndef SCN_STEP_WEAPON_COMBINATIONDEESHOT_PARAM_H
#define SCN_STEP_WEAPON_COMBINATIONDEESHOT_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdeeshot {

// TODO: name the members.
struct LevelParam {
    f32 _0;
    f32 _4;
};

struct Param {
    LevelParam _0;
    LevelParam _8;
    LevelParam _10;
    u32 _18;
};

}}}}  // namespace scn::step::weapon::combinationdeeshot

#endif
