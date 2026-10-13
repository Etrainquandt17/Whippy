#ifndef HEL_MATH_MATRIX34_H
#define HEL_MATH_MATRIX34_H

#include "hel/math/Direction3.h"
#include "hel/math/Vector3.h"
#include "revolution/mtx.h"
#include "types.h"

namespace hel {
namespace math {

class Direction3;
class Matrix44;

class Matrix34 {
public:
    Matrix34() { PSMTXIdentity(m); }
    Matrix34(const Matrix34& other) { PSMTXCopy(other.m, m); }

    // TODO: hel/math/Direction3.cpp defines HEL_MATH_MATRIX34_OUT_OF_LINE to get declarations: the relativePos
    // that the link dropped from it would be its second use of mul.
#ifdef HEL_MATH_MATRIX34_OUT_OF_LINE
    Matrix34& operator=(const Matrix34& other);
    Matrix34 operator*(const Matrix34& other) const;
    Vector3 mul(const Vector3& v) const;
    Vector3 getPos() const;
    Vector3 getT() const;
    void setT(const Vector3& v);
    static void MtxColVec(f32 (*mtx)[4], int col, Vec* out);
#else
    Matrix34& operator=(const Matrix34& other) {
        if (this == &other) {
            return *this;
        }
        PSMTXCopy(other.m, m);
        return *this;
    }

    Matrix34 operator*(const Matrix34& other) const {
        Matrix34 result;
        PSMTXConcat(m, other.m, result.m);
        return result;
    }

    Vector3 mul(const Vector3& v) const {
        Vector3 result;
        PSMTXMultVec(m, reinterpret_cast<const Vec*>(&v), reinterpret_cast<Vec*>(&result));
        return result;
    }

    Vector3 getPos() const {
        Vector3 result;
        result.x = m[0][3];
        result.y = m[1][3];
        result.z = m[2][3];
        return result;
    }

    Vector3 getT() const { return Vector3(m[0][3], m[1][3], m[2][3]); }

    void setT(const Vector3& v) {
        m[0][3] = v.x;
        m[1][3] = v.y;
        m[2][3] = v.z;
    }

    Vector3 getX() const { return Vector3(m[0][0], m[1][0], m[2][0]); }
    Vector3 getY() const { return Vector3(m[0][1], m[1][1], m[2][1]); }
    Vector3 getZ() const { return Vector3(m[0][2], m[1][2], m[2][2]); }

    void setX(const Vector3& v) {
        m[0][0] = v.x;
        m[1][0] = v.y;
        m[2][0] = v.z;
    }

    void setY(const Vector3& v) {
        m[0][1] = v.x;
        m[1][1] = v.y;
        m[2][1] = v.z;
    }

    void setZ(const Vector3& v) {
        m[0][2] = v.x;
        m[1][2] = v.y;
        m[2][2] = v.z;
    }

    static void MtxColVec(f32 (*mtx)[4], int col, Vec* out) {
        out->x = mtx[0][col];
        out->y = mtx[1][col];
        out->z = mtx[2][col];
    }

    static void MtxSetColVec(f32 (*mtx)[4], int col, const Vec* v) {
        mtx[0][col] = v->x;
        mtx[1][col] = v->y;
        mtx[2][col] = v->z;
    }

    Vector3 getVecFront() const {
        Vector3 result;
        MtxColVec(const_cast<f32 (*)[4]>(m), 2, reinterpret_cast<Vec*>(&result));
        return result;
    }
#endif

    static Matrix34 CreateTrans(const Vector3& trans);
    static Matrix34 CreateScale(const Vector3& scale);
    static Matrix34 CreateRotAxisRad(const Vector3& axis, f32 rad);
    static Matrix34 CreateRotAxisDeg(const Vector3& axis, f32 deg);
    static Matrix34 CreateRotXYZRad(const Vector3& rot);
    static Matrix34 CreateRotXYZDeg(const Vector3& rot);
    static Matrix34 CreateLookAt(const Vector3& pos, const Vector3& up, const Vector3& dir);

    Matrix44 toMatrix44() const;
    void mtxInverse(const f32 (*src)[4], f32 (*dst)[4]) const;

    Matrix34(const Direction3& direction, const Vector3& pos);

    f32 m[3][4];
};

#ifndef HEL_MATH_MATRIX34_OUT_OF_LINE
inline Matrix34::Matrix34(const Direction3& direction, const Vector3& pos) : m() {
    m[0][0] = direction.mLeft.x;
    m[1][0] = direction.mLeft.y;
    m[2][0] = direction.mLeft.z;
    m[0][1] = direction.mUp.x;
    m[1][1] = direction.mUp.y;
    m[2][1] = direction.mUp.z;
    m[0][2] = direction.mFront.x;
    m[1][2] = direction.mFront.y;
    m[2][2] = direction.mFront.z;
    m[0][3] = pos.x;
    m[1][3] = pos.y;
    m[2][3] = pos.z;
}
#endif

}}  // namespace hel::math

#endif
