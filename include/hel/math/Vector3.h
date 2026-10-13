#ifndef HEL_MATH_VECTOR3_H
#define HEL_MATH_VECTOR3_H

#include "hel/math/Math.h"
#include "hel/math/Vec3.h"
#include "hel/math/Vector2.h"
#include "nw4r/math/math_types.h"
#include "types.h"

namespace hel {
namespace math {

class Vector3 {
public:
    Vector3() { x = y = z = 0.0f; }
    // TODO: the original's copy constructor is the compiler's own, which copies the words: a unit that copies
    // once has the six word copies in place, and a unit that copies twice calls it. This inline one does both,
    // and with it a temporary is passed by value without a copy, as in the original. hero/Piggyback is closer
    // without a declared one (HEL_MATH_VECTOR3_NO_COPY_CONSTRUCTOR), and gimmick/block/Block copies once and
    // calls it, so it takes the declaration (HEL_MATH_VECTOR3_COPY_CONSTRUCTOR_OUT_OF_LINE) until its second
    // use is written.
#ifndef HEL_MATH_VECTOR3_NO_COPY_CONSTRUCTOR
#ifdef HEL_MATH_VECTOR3_COPY_CONSTRUCTOR_OUT_OF_LINE
    Vector3(const Vector3& other);
#else
    Vector3(const Vector3& other) { *reinterpret_cast<Words*>(this) = *reinterpret_cast<const Words*>(&other); }
#endif
#endif
    // TODO: a stand-in for a copy of the words. The two named references are what makes a unit that converts
    // twice call it; as one statement it is expanded everywhere, and with float copies it never copies words.
    Vector3(const Vec3& other) {
        const Words& from = reinterpret_cast<const Words&>(other);
        Words& to = reinterpret_cast<Words&>(*this);
        to = from;
    }
    Vector3(const nw4r::math::VEC3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // TODO: all of these are inline in the original. hel/math/Vector3.cpp defines
    // HEL_MATH_VECTOR3_OPERATORS_OUT_OF_LINE to get declarations: the place where it emits each
    // depends on functions of that unit which the link dropped. The assignment is the compiler's own.
#ifdef HEL_MATH_VECTOR3_OPERATORS_OUT_OF_LINE
    Vector3(f32 x, f32 y, f32 z);
    Vector3& operator=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(f32 scale);
    Vector3& operator/=(f32 scale);
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(f32 scale) const;
    f32 squareLength() const;
    f32 dot(const Vector3& other) const;
    f32 length() const;
    Vector3 cross(const Vector3& other) const;
    bool isZero() const;
    Vector3 operator/(f32 scale) const;
    void set(f32 x, f32 y, f32 z);
    bool equalsLoose(const Vector3& other, f32 epsilon) const;
    bool isZeroLoose(f32 epsilon) const;
    Vector2 getXY() const;
    Vector2 getXZ() const;
    Vector2 getYX() const;
    Vector2 getYZ() const;
    Vector2 getZX() const;
    Vector2 getZY() const;
    Vector3 getNormalized() const;
#else
    Vector3(f32 x_, f32 y_, f32 z_) : x(x_), y(y_), z(z_) {}

    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3& operator*=(f32 scale) {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3& operator/=(f32 scale) { return *this *= 1.0f / scale; }

    // TODO: the copies of *this stand in for the compiler's own copy of a named vector, word by word.
    Vector3 operator+(const Vector3& other) const {
        Words copy = *reinterpret_cast<const Words*>(this);
        return reinterpret_cast<Vector3&>(copy) += other;
    }

    Vector3 operator-(const Vector3& other) const {
        Words copy = *reinterpret_cast<const Words*>(this);
        return reinterpret_cast<Vector3&>(copy) -= other;
    }

    Vector3 operator*(f32 scale) const {
        Words copy = *reinterpret_cast<const Words*>(this);
        return reinterpret_cast<Vector3&>(copy) *= scale;
    }

    f32 squareLength() const { return x * x + y * y + z * z; }
    f32 dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
    f32 length() const { return Math::SqrtF(dot(*this)); }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    bool isZero() const { return x == ZERO.x && y == ZERO.y && z == ZERO.z; }

    Vector3 operator/(f32 scale) const {
        Words copy = *reinterpret_cast<const Words*>(this);
        return reinterpret_cast<Vector3&>(copy) /= scale;
    }

    void set(f32 x_, f32 y_, f32 z_) {
        x = x_;
        y = y_;
        z = z_;
    }

    bool equalsLoose(const Vector3& other, f32 epsilon) const {
        return Math::Equals(x, other.x, epsilon) && Math::Equals(y, other.y, epsilon) && Math::Equals(z, other.z, epsilon);
    }

    bool isZeroLoose(f32 epsilon) const { return equalsLoose(ZERO, epsilon); }

    Vector2 getXY() const { return Vector2(x, y); }
    Vector2 getXZ() const { return Vector2(x, z); }
    Vector2 getYX() const { return Vector2(y, x); }
    Vector2 getYZ() const { return Vector2(y, z); }
    Vector2 getZX() const { return Vector2(z, x); }
    Vector2 getZY() const { return Vector2(z, y); }

    Vector3 getNormalized() const {
        Vector3 result(*this);
        result.normalize();
        return result;
    }

    Vector3 operator-() const { return *this * -1.0f; }
    bool equalsStrict(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

    // TODO: the copy stands in for the compiler's own copy of a named vector, as in the operators above.
    f32 squareDistance(const Vector3& other) const {
        Words diff = reinterpret_cast<const Words&>(static_cast<const Vector3&>(other - *this));
        return reinterpret_cast<const Vector3&>(diff).squareLength();
    }

    f32 distance(const Vector3& other) const { return Math::Sqrtf(squareDistance(other)); }
#endif

    enum AxisKind {
        AXIS_X,
        AXIS_Y,
        AXIS_Z,
    };

    f32 normalize();
    f32 permittedNormalize();
    Vector3 normalizedCross(const Vector3& other) const;
    Vector3 permittedNormalizedCross(const Vector3& other) const;
    f32 setLength(f32 length);
    Vector3 getVertical(const Vector3& other) const;
    void projection(const Vector3& normal);
    f32 cos(const Vector3& other) const;
    void rotate(const Vector3& axis, f32 angle);
    void rotate(AxisKind axis, f32 angle);
    Vector3 slerp(const Vector3& other, f32 t) const;
    void reflect(const Vector3& normal, f32 restitution);
    void scale(const Vector3& other);
    Vector3 getScaled(const Vector3& other) const;

    bool isZeroStrict() const;

    static const Vector3 ZERO;
    static const Vector3 ALL_ONE;
    static const Vector3 BASIS_X;
    static const Vector3 BASIS_Y;
    static const Vector3 BASIS_Z;

    f32 x;
    f32 y;
    f32 z;

private:
    struct Words {
        u32 words[3];
    };
};

}
}

#endif
