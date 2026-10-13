#ifndef SCN_STEP_ENEMY_FLAMER_PARAMDATA_H
#define SCN_STEP_ENEMY_FLAMER_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

// TODO: the name is a guess: nothing in the game names what Param::flamer() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[33];
    s32 mAttackNum;
};

}}}}  // namespace scn::step::enemy::flamer

#endif
