#ifndef HEL_MATH_MATRIX44_H
#define HEL_MATH_MATRIX44_H

#include "nw4r/math/math_types.h"
#include "types.h"

namespace hel {
namespace math {

class Vector3;

class Matrix44 {
public:
    Matrix44();
    Matrix44(const Matrix44& other) { nw4r::math::MTX44Copy(&m, &other.m); }
    // TODO: the attribute is a stand-in. The original keeps the calls to this constructor in the
    // Create functions, and this compiler expands them without it; why is not known.
    Matrix44(const nw4r::math::MTX44& mtx) __attribute__((never_inline));

    static Matrix44 CreateFrustum(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
    static Matrix44 CreatePerspective(f32 fovy, f32 aspect, f32 near, f32 far);
    static Matrix44 CreateOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);

    Matrix44 mulMtx(const Matrix44& other) const;
    Vector3 mulVec(const Vector3& vec) const;

    nw4r::math::MTX44 m;
};

}}  // namespace hel::math

#endif
