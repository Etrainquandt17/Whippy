#ifndef SCN_STEP_WEAPON_STARSHOTLV1_PARAM_H
#define SCN_STEP_WEAPON_STARSHOTLV1_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv1 {

// TODO: name the members.
struct Param {
    u32 mScaleFrame;
    f32 mAttackRadius;
    f32 mAttackSubOffset;
    f32 mReflectSpeedV;
    f32 mResistSpeedRateH;
    f32 mResistSpeedV;
    f32 mRotSpeed;
    f32 mWaterMoveRate;
};

}}}}  // namespace scn::step::weapon::starshotlv1

#endif
