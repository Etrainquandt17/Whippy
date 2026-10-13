#define HEL_MATH_VECTOR2_OUT_OF_LINE
#include "hel/math/Vector2.h"

#include "hel/math/Vector3.h"
#include "nw4r/math/math_arithmetic.h"
#include "std/cmath.h"

namespace hel {
namespace math {

const Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);
const Vector2 Vector2::ALL_ONE = Vector2(1.0f, 1.0f);
const Vector2 Vector2::BASIS_X = Vector2(1.0f, 0.0f);
const Vector2 Vector2::BASIS_Y = Vector2(0.0f, 1.0f);

f32 Vector2::length() const {
    return nw4r::math::FSqrt(squareLength());
}

f32 Vector2::squareLength() const {
    return dot(*this);
}

f32 Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector2& Vector2::operator*=(f32 scale) {
    x *= scale;
    y *= scale;
    return *this;
}

f32 Vector2::normalize() {
    f32 len = length();
    if (len == 0.0f) {
        return len;
    }
    *this /= len;
    if (1.0f <= x) {
        x = 1.0f;
        y = 0.0f;
    } else if (x <= -1.0f) {
        x = -1.0f;
        y = 0.0f;
    } else if (1.0f <= y) {
        y = 1.0f;
        x = 0.0f;
    } else if (y <= -1.0f) {
        y = -1.0f;
        x = 0.0f;
    }
    return len;
}

Vector2& Vector2::operator/=(f32 scale) {
    return *this *= 1.0f / scale;
}

f32 Vector2::setLength(f32 length_) {
    f32 len = length();
    if (len == 0.0f) {
        *this = ZERO;
    } else {
        *this *= length_ / len;
    }
    return len;
}

Vector2& Vector2::operator=(const Vector2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

f32 Vector2::cos(const Vector2& other) const {
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

f32 Vector2::signedAngle(const Vector2& other) const {
    f32 len = length() * other.length();
    if (len < 0.00001f) {
        return 0.0f;
    }
    f32 c = dot(other) / len;
    if (c > 1.0f) {
        return 0.0f;
    } else if (c < -1.0f) {
        return 3.1415927f;
    }
    if (x * other.y - y * other.x < 0.0f) {
        return -acosf(c);
    }
    return acosf(c);
}

void Vector2::rotate(f32 angle) {
    f32 s = static_cast<f32>(sin(angle));
    f32 c = static_cast<f32>(::cos(angle));
    Vector2 rotated(x * c - y * s, x * s + y * c);
    set(rotated.x, rotated.y);
}

void Vector2::set(f32 x_, f32 y_) {
    x = x_;
    y = y_;
}

Vector2 Vector2::operator*(f32 scale) const {
    return Vector2(*this) *= scale;
}

Vector2 Vector2::getNormalized() const {
    Vector2 result(*this);
    result.normalize();
    return result;
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

void Vector2::scale(const Vector2& other) {
    x *= other.x;
    y *= other.y;
}

Vector3 Vector2::toVector3() const {
    return Vector3(x, y, 0.0f);
}

Vector3 Vector2::toVector3XOY() const {
    return Vector3(x, 0.0f, y);
}

Vector2::Vector2() {
    y = 0.0f;
    x = 0.0f;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2::Vector2(f32 x_, f32 y_)
    : x(x_)
    , y(y_) {}

Vector2::Vector2(const Vector2& other)
    : x(other.x)
    , y(other.y) {}

}}  // namespace hel::math
