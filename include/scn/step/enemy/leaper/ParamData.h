#ifndef SCN_STEP_ENEMY_LEAPER_PARAMDATA_H
#define SCN_STEP_ENEMY_LEAPER_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

// TODO: the name is a guess: nothing in the game names what Param::leaper() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[8];
    u32 mShotFrame;
};

}}}}  // namespace scn::step::enemy::leaper

#endif
