#ifndef SCN_STEP_ENEMY_DUBIORSPARK_PARAMDATA_H
#define SCN_STEP_ENEMY_DUBIORSPARK_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorspark {

// TODO: the name is a guess: nothing in the game names what Param::dubiorspark() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamDecel mDecel;
};

}}}}  // namespace scn::step::enemy::dubiorspark

#endif
