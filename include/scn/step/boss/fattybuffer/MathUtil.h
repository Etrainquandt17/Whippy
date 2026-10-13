#ifndef SCN_STEP_BOSS_FATTYBUFFER_MATHUTIL_H
#define SCN_STEP_BOSS_FATTYBUFFER_MATHUTIL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

// TODO: an inline function of hel::math, whose name is not known: Math::LinearInterpolation multiplies the other way round.
inline f32 t_Interpolate(const f32& value, const f32& target, f32 rate) {
    return rate * (target - value) + value;
}

}}}}  // namespace scn::step::boss::fattybuffer

#endif
