#include "hel/math/Matrix44.h"

#include "hel/math/Vector3.h"
#include "revolution/mtx.h"

namespace hel {
namespace math {

Matrix44 Matrix44::CreateFrustum(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far) {
    nw4r::math::MTX44 mtx;
    C_MTXFrustum(mtx, top, bottom, left, right, near, far);
    return Matrix44(mtx);
}

Matrix44 Matrix44::CreatePerspective(f32 fovy, f32 aspect, f32 near, f32 far) {
    nw4r::math::MTX44 mtx;
    C_MTXPerspective(mtx, fovy, aspect, near, far);
    return Matrix44(mtx);
}

Matrix44 Matrix44::CreateOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far) {
    nw4r::math::MTX44 mtx;
    C_MTXOrtho(mtx, top, bottom, left, right, near, far);
    return Matrix44(mtx);
}

Matrix44::Matrix44() {
    nw4r::math::MTX44Identity(&m);
}

Matrix44::Matrix44(const nw4r::math::MTX44& mtx) {
    nw4r::math::MTX44Copy(&m, &mtx);
}

Matrix44 Matrix44::mulMtx(const Matrix44& other) const {
    Matrix44 result;
    PSMTX44Concat(m, other.m, result.m);
    return result;
}

Vector3 Matrix44::mulVec(const Vector3& vec) const {
    Vec result;
    PSMTX44MultVec(m, reinterpret_cast<const Vec*>(&vec), &result);
    return Vector3(nw4r::math::VEC3(result));
}

}}  // namespace hel::math
