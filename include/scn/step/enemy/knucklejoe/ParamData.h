#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_PARAMDATA_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

// TODO: the name is a guess: nothing in the game names what Param::knucklejoe() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mSpeed[3];
    u32 _c[10];
    u32 mHadouFrame;
    u32 _38[7];
    u32 mVulcanFrame;
    u32 _58[2];
    u32 mAttackRepeatMax;
};

}}}}  // namespace scn::step::enemy::knucklejoe

#endif
