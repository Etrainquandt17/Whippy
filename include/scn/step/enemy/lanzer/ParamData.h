#ifndef SCN_STEP_ENEMY_LANZER_PARAMDATA_H
#define SCN_STEP_ENEMY_LANZER_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

// TODO: the name is a guess: nothing in the game names what Param::lanzer() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSpeed[3];
};

}}}}  // namespace scn::step::enemy::lanzer

#endif
