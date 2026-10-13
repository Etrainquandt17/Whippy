#ifndef NW4R_MATH_TRIANGULAR_H
#define NW4R_MATH_TRIANGULAR_H

#include "std/cmath.h"
#include "types.h"

// An angle as an index into the sine table: 256 to the full turn.
#define NW4R_MATH_RAD_TO_FIDX(rad) (40.743664f * (rad))
#define NW4R_MATH_FIDX_TO_RAD(fidx) (0.024543693f * (fidx))
#define NW4R_MATH_DEG_TO_FIDX(deg) (0.7111111f * (deg))
#define NW4R_MATH_FIDX_TO_DEG(fidx) (1.40625f * (fidx))

namespace nw4r {
namespace math {

f32 SinFIdx(f32 fidx);
f32 CosFIdx(f32 fidx);
f32 Atan2FIdx(f32 y, f32 x);

inline f32 TanFIdx(f32 fidx) {
    return tanf(NW4R_MATH_FIDX_TO_RAD(fidx));
}

inline f32 SinRad(f32 rad) {
    return SinFIdx(NW4R_MATH_RAD_TO_FIDX(rad));
}

inline f32 CosRad(f32 rad) {
    return CosFIdx(NW4R_MATH_RAD_TO_FIDX(rad));
}

inline f32 TanRad(f32 rad) {
    return TanFIdx(NW4R_MATH_RAD_TO_FIDX(rad));
}

}}  // namespace nw4r::math

#endif
