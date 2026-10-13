#ifndef SCN_STEP_ENEMY_METALGENERALBALL_PARAMDATA_H
#define SCN_STEP_ENEMY_METALGENERALBALL_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralball {

// TODO: the name is a guess: nothing in the game names what Param::metalgeneralball() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    u32 _0[2];
    f32 mScale;
    u32 _c;
    u32 mBeamFrame;
};

}}}}  // namespace scn::step::enemy::metalgeneralball

#endif
