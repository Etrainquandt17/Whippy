#ifndef SCN_STEP_ENEMY_PACTO_PARAMDATA_H
#define SCN_STEP_ENEMY_PACTO_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

// TODO: the name is a guess: nothing in the game names what Param::pacto() returns. The members named after
// their offsets are not known yet.
struct ParamData {
    f32 mDiveDist;
    f32 mDiveSpeed;
    int mBiteSoundWait;
    int mBiteFrame;
    u32 mEatDamageInterval;
    u32 mEatDamageIntervalSuper;
    u32 mEatFirstDamage;
    u32 mEatDamage;
    u32 mEatFrame;
    u32 mSpitEndFrame;
    f32 mBackSpeed;
};

}}}}  // namespace scn::step::enemy::pacto

#endif
