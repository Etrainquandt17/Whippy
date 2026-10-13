#ifndef SCN_STEP_ENEMY_AQUAROCK_PARAMDATA_H
#define SCN_STEP_ENEMY_AQUAROCK_PARAMDATA_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

// TODO: the name is a guess: nothing in the game names what Param::aquarock() returns.
struct ParamData {
    f32 mDiameterSmall;
    f32 mDiameterMiddle;
    f32 mDiameterLarge;
    f32 mSpeedLevel0;
    f32 mSpeedLevel1;
    f32 mSpeedLevel2;
    f32 _18;
    f32 mAngleSpeedRate;
    f32 _20;
    f32 _24;
    f32 _28;
    f32 _2c;
    f32 _30;
    f32 _34;
    u32 _38;
    u32 mShakeFrame;
    f32 mShakeRate;
};

}}}}  // namespace scn::step::enemy::aquarock

#endif
