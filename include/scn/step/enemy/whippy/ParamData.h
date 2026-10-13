#ifndef SCN_STEP_ENEMY_WHIPPY_PARAMDATA_H
#define SCN_STEP_ENEMY_WHIPPY_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

// TODO: the name is a guess: nothing in the game names what Param::whippy() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mAngleMax;
    u32 mAimFrame;
    u32 mReturnFrame;
    u32 mAntennaFrame;
};

}}}}  // namespace scn::step::enemy::whippy

#endif
