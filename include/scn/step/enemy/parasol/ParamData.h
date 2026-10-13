#ifndef SCN_STEP_ENEMY_PARASOL_PARAMDATA_H
#define SCN_STEP_ENEMY_PARASOL_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

// TODO: the name is a guess: nothing in the game names what Param::parasol() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    gobj::MoveParamAccel mAccel;
    gobj::MoveParamFall mFall;
};

}}}}  // namespace scn::step::enemy::parasol

#endif
