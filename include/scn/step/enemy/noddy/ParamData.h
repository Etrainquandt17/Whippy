#ifndef SCN_STEP_ENEMY_NODDY_PARAMDATA_H
#define SCN_STEP_ENEMY_NODDY_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

// TODO: the name is a guess: nothing in the game names what Param::noddy() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamAccel mAccel;
};

}}}}  // namespace scn::step::enemy::noddy

#endif
