#ifndef SCN_STEP_ENEMY_GLUNK_PARAMDATA_H
#define SCN_STEP_ENEMY_GLUNK_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

// TODO: the name is a guess: nothing in the game names what Param::glunk() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 mShotFrame;
};

}}}}  // namespace scn::step::enemy::glunk

#endif
