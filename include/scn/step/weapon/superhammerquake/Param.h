#ifndef SCN_STEP_WEAPON_SUPERHAMMERQUAKE_PARAM_H
#define SCN_STEP_WEAPON_SUPERHAMMERQUAKE_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace superhammerquake {

// TODO: name the members; the ones not seen in use yet are taken to be words.
struct LevelParam {
    u32 _0;
    u32 _4[8];
};

struct Param {
    u32 _0;
    u32 _4;
    LevelParam _8;
    LevelParam _2C;
    LevelParam _50;
};

}}}}  // namespace scn::step::weapon::superhammerquake

#endif
