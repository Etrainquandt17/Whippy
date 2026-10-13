#include "hel/math/Matrix34.h"

#include "hel/math/Matrix44.h"
#include "hel/math/Vector3.h"
#include "nw4r/math/math_types.h"
#include "revolution/mtx.h"
#include "std/cmath.h"

namespace hel {
namespace math {

Matrix34 Matrix34::CreateTrans(const Vector3& trans) {
    Matrix34 result;
    PSMTXTransApply(result.m, result.m, trans.x, trans.y, trans.z);
    return result;
}

Matrix34 Matrix34::CreateScale(const Vector3& scale) {
    Matrix34 result;
    PSMTXScaleApply(result.m, result.m, scale.x, scale.y, scale.z);
    return result;
}

Matrix34 Matrix34::CreateRotAxisRad(const Vector3& axis, f32 rad) {
    Matrix34 result;
    nw4r::math::MTX34RotAxisRad(reinterpret_cast<nw4r::math::MTX34*>(&result), reinterpret_cast<const nw4r::math::VEC3*>(&axis), rad);
    return result;
}

Matrix34 Matrix34::CreateRotAxisDeg(const Vector3& axis, f32 deg) {
    Matrix34 result;
    nw4r::math::MTX34RotAxisDeg(reinterpret_cast<nw4r::math::MTX34*>(&result), reinterpret_cast<const nw4r::math::VEC3*>(&axis), deg);
    return result;
}

Matrix34 Matrix34::CreateRotXYZRad(const Vector3& rot) {
    Matrix34 result;
    nw4r::math::MTX34RotXYZRad(reinterpret_cast<nw4r::math::MTX34*>(&result), rot.x, rot.y, rot.z);
    return result;
}

Matrix34 Matrix34::CreateRotXYZDeg(const Vector3& rot) {
    Matrix34 result;
    nw4r::math::MTX34RotXYZDeg(reinterpret_cast<nw4r::math::MTX34*>(&result), rot.x, rot.y, rot.z);
    return result;
}

Matrix34 Matrix34::CreateLookAt(const Vector3& pos, const Vector3& up, const Vector3& dir) {
    Matrix34 result;
    C_MTXLookAt(result.m, reinterpret_cast<const Vec*>(&pos), reinterpret_cast<const Vec*>(&up), reinterpret_cast<const Vec*>(&dir));
    return result;
}

Matrix44 Matrix34::toMatrix44() const {
    Matrix44 result;
    result.m.m[0][0] = m[0][0];
    result.m.m[0][1] = m[0][1];
    result.m.m[0][2] = m[0][2];
    result.m.m[0][3] = m[0][3];
    result.m.m[1][0] = m[1][0];
    result.m.m[1][1] = m[1][1];
    result.m.m[1][2] = m[1][2];
    result.m.m[1][3] = m[1][3];
    result.m.m[2][0] = m[2][0];
    result.m.m[2][1] = m[2][1];
    result.m.m[2][2] = m[2][2];
    result.m.m[2][3] = m[2][3];
    return result;
}

void Matrix34::mtxInverse(const f32 (*src)[4], f32 (*dst)[4]) const {
    f32 det = src[0][0] * src[1][1] * src[2][2] + src[0][1] * src[1][2] * src[2][0] + src[0][2] * src[1][0] * src[2][1]
            - src[2][0] * src[1][1] * src[0][2] - src[1][0] * src[0][1] * src[2][2] - src[0][0] * src[2][1] * src[1][2];
    if (std::fabs(det) < 0.00001f) {
        PSMTXIdentity(dst);
        return;
    }
    Mtx tmp;
    if (src == dst) {
        PSMTXCopy(src, tmp);
        src = tmp;
    }
    f32 invDet = 1.0f / det;
    dst[0][0] = invDet * (src[1][1] * src[2][2] - src[2][1] * src[1][2]);
    dst[0][1] = invDet * -(src[0][1] * src[2][2] - src[2][1] * src[0][2]);
    dst[0][2] = invDet * (src[0][1] * src[1][2] - src[1][1] * src[0][2]);
    dst[1][0] = invDet * -(src[1][0] * src[2][2] - src[2][0] * src[1][2]);
    dst[1][1] = invDet * (src[0][0] * src[2][2] - src[2][0] * src[0][2]);
    dst[1][2] = invDet * -(src[0][0] * src[1][2] - src[1][0] * src[0][2]);
    dst[2][0] = invDet * (src[1][0] * src[2][1] - src[2][0] * src[1][1]);
    dst[2][1] = invDet * -(src[0][0] * src[2][1] - src[2][0] * src[0][1]);
    dst[2][2] = invDet * (src[0][0] * src[1][1] - src[1][0] * src[0][1]);
    dst[0][3] = -dst[0][0] * src[0][3] - dst[0][1] * src[1][3] - dst[0][2] * src[2][3];
    dst[1][3] = -dst[1][0] * src[0][3] - dst[1][1] * src[1][3] - dst[1][2] * src[2][3];
    dst[2][3] = -dst[2][0] * src[0][3] - dst[2][1] * src[1][3] - dst[2][2] * src[2][3];
}

}
}
