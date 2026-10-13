#ifndef HEL_MATH_MATH_H
#define HEL_MATH_MATH_H

#include "nw4r/math/math_arithmetic.h"
#include "nw4r/math/math_triangular.h"
#include "types.h"

namespace hel {
namespace math {

class Math {
public:
    static f32 DegToRad(f32 deg) { return 0.017453292f * deg; }

    static f32 SinF(f32 rad) { return nw4r::math::SinRad(rad); }
    static f32 CosF(f32 rad) { return nw4r::math::CosRad(rad); }
    static f32 TanF(f32 rad) { return nw4r::math::TanRad(rad); }
    // The factor stands in the body: through DegToRad() the two constants come out in the other order.
    static f32 SinDegF(f32 deg) { return SinF(0.017453292f * deg); }
    static f32 CosDegF(f32 deg) { return CosF(0.017453292f * deg); }
    static f32 Atan2DegF(f32 y, f32 x) { return NW4R_MATH_FIDX_TO_DEG(nw4r::math::Atan2FIdx(y, x)); }

    static bool Equals(f32 a, f32 b, f32 epsilon) { return -epsilon < a - b && a - b < epsilon; }
    static f32 FloorF(f32 value);
    static f32 SqrtF(f32 value) { return nw4r::math::FSqrt(value); }
    static f32 Sqrtf(f32 value);

    template <typename T>
    static const T Limit(const T& value, const T& limit) {
        if (value > limit) {
            return limit;
        }
        if (value < -limit) {
            return -limit;
        }
        return value;
    }

    template <typename T>
    static const T& Max(const T& a, const T& b) {
        return a > b ? a : b;
    }

    template <typename T>
    static const T& Min(const T& a, const T& b) {
        return a < b ? a : b;
    }

    template <typename T>
    static const T LimitMax(const T& value, const T& max) {
        if (value > max) {
            return max;
        }
        return value;
    }

    template <typename T>
    static const T LimitMin(const T& value, const T& min) {
        if (value < min) {
            return min;
        }
        return value;
    }

    template <typename T>
    static const T LimitMinMax(const T& value, const T& min, const T& max) {
        if (value > max) {
            return max;
        }
        if (value < min) {
            return min;
        }
        return value;
    }

    template <typename T>
    static const T Abs(T value) {
        return value < 0 ? -value : value;
    }

    static f32 AbsF32(f32 value) { return Abs(value); }
    static f32 SignF32(f32 value) { return static_cast<f32>(value < 0.0f ? -1 : 1); }

    template <typename T>
    static s8 Sign(const T& value) {
        return value < 0 ? -1 : 1;
    }

    template <typename T>
    static const T LinearInterpolation(const T& a, const T& b, f32 rate) {
        return (b - a) * rate + a;
    }

    // TODO: the name is a guess: the function is expanded wherever it is used, so the link map does not have it.
    template <typename T>
    static const T Interpolate(const T& value, const T& target, f32 rate) {
        return rate * (target - value) + value;
    }

    // TODO: the name is a guess: the function is expanded wherever it is used, so the link map does not have it.
    template <typename T>
    static const T Square(const T& value) {
        return value * value;
    }

    static f32 InterpolationParamMinToMax(f32 t) { return 1.5f * (t * t) - 0.5f * t * (t * t); }
    static f32 InterpolationParamMinToMin(f32 t) { return 3.0f * (t * t) - 2.0f * t * (t * t); }

    static bool EqZero(f32 value) {
        if (value < 0.00001f && value > -0.00001f) {
            return true;
        }
        return false;
    }
};

}}  // namespace hel::math

#endif
