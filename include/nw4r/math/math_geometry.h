#ifndef NW4R_MATH_GEOMETRY_H
#define NW4R_MATH_GEOMETRY_H

#include "nw4r/math/math_types.h"
#include "types.h"

namespace nw4r {
namespace math {

struct SEGMENT3 {
    SEGMENT3() {}
    SEGMENT3(const VEC3& p0, const VEC3& p1) : P0(p0), P1(p1) {}

    VEC3 P0;
    VEC3 P1;
};

struct SPHERE {
    SPHERE() {}
    SPHERE(const VEC3& center, f32 radius) : C(center), r(radius) {}

    VEC3 C;
    f32 r;
};

struct CAPSULE {
    CAPSULE() {}
    CAPSULE(const VEC3& p0, const VEC3& p1, f32 radius) : S(p0, p1), r(radius) {}

    SEGMENT3 S;
    f32 r;
};

int IntersectionSegment3Sphere(const SEGMENT3* segment, const SPHERE* sphere, f32* t0, f32* t1);
bool IntersectionCapsule(const CAPSULE* c0, const CAPSULE* c1);

}
}

#endif
