#ifndef SCN_STEP_ENEMY_WADDLEDOO_PARAMDATA_H
#define SCN_STEP_ENEMY_WADDLEDOO_PARAMDATA_H

#include "gobj/MoveParam.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

// TODO: the name is a guess: nothing in the game names what Param::waddledoo() returns.
struct ParamData {
    f32 mJumpSpeed;
    gobj::MoveParamAccel mJumpAccel;
    gobj::MoveParamFall mJumpFall;
};

}}}}  // namespace scn::step::enemy::waddledoo

#endif
