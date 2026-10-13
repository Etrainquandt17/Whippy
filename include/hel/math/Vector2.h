#ifndef HEL_MATH_VECTOR2_H
#define HEL_MATH_VECTOR2_H

#include "hel/math/Math.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace hel {
namespace math {

class Vector3;

class Vector2 {
public:
    // TODO: all of these are inline in the original. A unit that defines HEL_MATH_VECTOR2_OUT_OF_LINE ahead of
    // its includes gets declarations: hel/math/Vector2.cpp, where the place of each depends on functions the link
    // dropped, and gimmick/warplowper/WarpLowper, which lacks the second use of the copy constructor.
    // The assignment is the compiler's own, which is why a class that holds a vector is assigned by words.
#ifdef HEL_MATH_VECTOR2_OUT_OF_LINE
    Vector2();
    Vector2(f32 x, f32 y);
    Vector2(const Vector2& other);

    void set(f32 x, f32 y);
    f32 dot(const Vector2& other) const;
    f32 squareLength() const;
    f32 length() const;
    bool isZeroStrict() const;
    bool isZero() const;
    bool isZeroLoose(f32 epsilon) const;

    Vector2& operator=(const Vector2& other);
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(f32 scale);
    Vector2& operator/=(f32 scale);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(f32 scale) const;
    Vector2 operator/(f32 scale) const;
#else
    Vector2() { x = y = 0.0f; }
    Vector2(f32 x_, f32 y_) : x(x_), y(y_) {}
    // TODO: the copy constructor is the compiler's own in the original: a unit that copies twice or more calls
    // it while the operators stay expanded. Such a unit defines HEL_MATH_VECTOR2_COPY_CONSTRUCTOR_OUT_OF_LINE.
#ifdef HEL_MATH_VECTOR2_COPY_CONSTRUCTOR_OUT_OF_LINE
    Vector2(const Vector2& other);
#else
    Vector2(const Vector2& other) : x(other.x), y(other.y) {}
#endif

    void set(f32 x_, f32 y_) {
        x = x_;
        y = y_;
    }

    f32 dot(const Vector2& other) const { return x * other.x + y * other.y; }
    f32 squareLength() const { return dot(*this); }
    f32 length() const { return Math::SqrtF(squareLength()); }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(f32 scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2& operator/=(f32 scale) { return *this *= 1.0f / scale; }

    Vector2 operator+(const Vector2& other) const { return Vector2(*this) += other; }
    Vector2 operator-(const Vector2& other) const { return Vector2(*this) -= other; }
    Vector2 operator*(f32 scale) const { return Vector2(*this) *= scale; }
    Vector2 operator/(f32 scale) const { return Vector2(*this) /= scale; }
    Vector2 operator-() const { return *this * -1.0f; }

    bool equalsStrict(const Vector2& other) const { return x == other.x && y == other.y; }

    f32 squareDistance(const Vector2& other) const {
        f32 dx = x - other.x;
        f32 dy = y - other.y;
        return dx * dx + dy * dy;
    }

    f32 distance(const Vector2& other) const { return Math::SqrtF(squareDistance(other)); }
    bool isZeroStrict() const { return x == ZERO.x && y == ZERO.y; }
    bool isZero() const { return isZeroStrict(); }

    bool equalsLoose(const Vector2& other, f32 epsilon) const {
        return Math::Equals(x, other.x, epsilon) && Math::Equals(y, other.y, epsilon);
    }

    bool isZeroLoose(f32 epsilon) const { return equalsLoose(ZERO, epsilon); }
#endif
    Vector2(const Vec2& other) {
        x = other.x;
        y = other.y;
    }

    Vector3 toVector3() const;
    Vector3 toVector3XOY() const;

    f32 normalize();
    f32 setLength(f32 length);
    f32 cos(const Vector2& other) const;
    f32 signedAngle(const Vector2& other) const;
    void rotate(f32 angle);
    // TODO: inline in the original. A unit that expands it defines HEL_MATH_VECTOR2_GETNORMALIZED_IN_CLASS ahead of
    // its includes.
#ifdef HEL_MATH_VECTOR2_GETNORMALIZED_IN_CLASS
    Vector2 getNormalized() const {
        Vector2 result(*this);
        result.normalize();
        return result;
    }
#else
    Vector2 getNormalized() const;
#endif
    void scale(const Vector2& other);

    // TODO: the copy is word by word in the original, as if Vector2 were built on Vec2.
    operator Vec2() const { return reinterpret_cast<const Vec2&>(*this); }

    static const Vector2 ZERO;
    static const Vector2 ALL_ONE;
    static const Vector2 BASIS_X;
    static const Vector2 BASIS_Y;

    f32 x;
    f32 y;
};

}}  // namespace hel::math

#endif
