#define HEL_MATH_VECTOR3_OPERATORS_OUT_OF_LINE
#include "hel/math/Vector3.h"

#include "nw4r/math/math_triangular.h"
#include "nw4r/math/math_types.h"
#include "std/cmath.h"

namespace hel {
namespace math {

const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ALL_ONE = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::BASIS_X = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::BASIS_Y = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::BASIS_Z = Vector3(0.0f, 0.0f, 1.0f);

Vector3 Vector3::normalizedCross(const Vector3& other) const {
    Vector3 result = cross(other);
    result.normalize();
    return result;
}

Vector3 Vector3::permittedNormalizedCross(const Vector3& other) const {
    Vector3 result = cross(other);
    if (result.permittedNormalize() == 0.0f) {
        return Vector3();
    }
    return result;
}

f32 Vector3::permittedNormalize() {
    if (length() == 0.0f) {
        return 0.0f;
    }
    return normalize();
}

f32 Vector3::normalize() {
    f32 len = length();
    if (len == 0.0f) {
        return len;
    }
    *this /= len;
    if (1.0f <= x) {
        x = 1.0f;
        z = 0.0f;
        y = 0.0f;
    } else if (x <= -1.0f) {
        x = -1.0f;
        z = 0.0f;
        y = 0.0f;
    } else if (1.0f <= y) {
        y = 1.0f;
        x = 0.0f;
        z = 0.0f;
    } else if (y <= -1.0f) {
        y = -1.0f;
        x = 0.0f;
        z = 0.0f;
    } else if (1.0f <= z) {
        z = 1.0f;
        y = 0.0f;
        x = 0.0f;
    } else if (z <= -1.0f) {
        z = -1.0f;
        y = 0.0f;
        x = 0.0f;
    }
    return len;
}

Vector3& Vector3::operator/=(f32 scale) {
    return *this *= 1.0f / scale;
}

Vector3& Vector3::operator*=(f32 scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

f32 Vector3::setLength(f32 length_) {
    f32 len = length();
    if (len == 0.0f) {
        *this = ZERO;
    } else {
        *this *= length_ / len;
    }
    return len;
}

f32 Vector3::cos(const Vector3& other) const {
    f32 len = length() * other.length();
    if (len == 0.0f) {
        return 0.0f;
    }
    f32 result = dot(other) / len;
    if (1.0f < result) {
        return 1.0f;
    } else if (result < -1.0f) {
        return -1.0f;
    }
    return result;
}

// TODO: getVertical and projection are unused and were dropped by the linker. They are rebuilt
// from their names and sizes alone and are not verified. Without them the inline functions they
// share with the rest of the file (the default constructor, std::fabs, operator+=) have one
// caller each and are expanded, which the original does not do.
Vector3 Vector3::getVertical(const Vector3& other) const {
    Vector3 result = cross(other);
    if (result.permittedNormalize() == 0.0f) {
        return Vector3();
    }
    return result.cross(*this);
}

bool Vector3::isZeroStrict() const {
    return x == ZERO.x && y == ZERO.y && z == ZERO.z;
}

void Vector3::rotate(const Vector3& axis, f32 angle) {
    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34RotAxisFIdx(&mtx, reinterpret_cast<const nw4r::math::VEC3*>(&axis), NW4R_MATH_RAD_TO_FIDX(angle));
    *this = Vector3(mtx._00 * x + mtx._01 * y + mtx._02 * z + mtx._03, mtx._10 * x + mtx._11 * y + mtx._12 * z + mtx._13,
                    mtx._20 * x + mtx._21 * y + mtx._22 * z + mtx._23);
}

void Vector3::rotate(AxisKind axis, f32 angle) {
    switch (axis) {
    case AXIS_X:
        rotate(BASIS_X, angle);
        break;
    case AXIS_Y:
        rotate(BASIS_Y, angle);
        break;
    case AXIS_Z:
        rotate(BASIS_Z, angle);
        break;
    }
}

Vector3 Vector3::slerp(const Vector3& other, f32 t) const {
    f32 c = dot(other);
    f32 s0;
    if (1.0f + c > 0.00001f) {
        if (1.0f - c > 0.00001f) {
            f32 omega = acosf(c);
            f32 sinOmega = sinf(omega);
            s0 = sinf((1.0f - t) * omega) / sinOmega;
            t = sinf(t * omega) / sinOmega;
        } else {
            s0 = 1.0f - t;
        }
        return *this * s0 + other * t;
    }
    Vector3 perp(-y, x, 0.0f);
    if (t < 0.5f) {
        s0 = sinf(1.5707964f * (1.0f - 2.0f * t));
        return *this * s0 + perp * sinf(1.5707964f * (2.0f * t));
    }
    t -= 0.5f;
    s0 = sinf(1.5707964f * (1.0f - 2.0f * t));
    return perp * s0 + other * sinf(1.5707964f * (2.0f * t));
}

void Vector3::projection(const Vector3& normal) {
    f32 d = dot(normal);
    if (std::fabs(d) > 0.00001f) {
        *this += normal * -d;
    }
}

void Vector3::reflect(const Vector3& normal, f32 restitution) {
    f32 d = dot(normal);
    if (std::fabs(d) > 0.00001f) {
        *this += normal * ((-1.0f - restitution) * d);
    }
}

void Vector3::scale(const Vector3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
}

Vector3 Vector3::getScaled(const Vector3& other) const {
    Vector3 result(*this);
    result.scale(other);
    return result;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

}
}
