#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H

#include "revolution/mtx.h"
#include "types.h"

namespace nw4r {
namespace math {

struct _VEC3 {
    f32 x;
    f32 y;
    f32 z;
};

struct VEC3;

VEC3* VEC3Add(register VEC3* out, register const VEC3* a, register const VEC3* b);

struct VEC3 : public _VEC3 {
    VEC3() {}
    VEC3(f32 fx, f32 fy, f32 fz);
    VEC3(const Vec& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    VEC3& operator+=(const VEC3& other) {
        VEC3Add(this, this, &other);
        return *this;
    }
};

inline VEC3* VEC3Add(register VEC3* out, register const VEC3* a, register const VEC3* b) {
    register f32 work0;
    register f32 work1;
    register f32 work2;

    asm {
        psq_l   work0, VEC3.x(a), 0, 0
        psq_l   work1, VEC3.x(b), 0, 0
        ps_add  work2, work0, work1
        psq_st  work2, VEC3.x(out), 0, 0
        psq_l   work0, VEC3.z(a), 1, 0
        psq_l   work1, VEC3.z(b), 1, 0
        ps_add  work2, work0, work1
        psq_st  work2, VEC3.z(out), 1, 0
    }
    return out;
}

struct _MTX34 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };
        f32 m[3][4];
        f32 a[12];
        Mtx mtx;
    };
};

struct MTX34 : public _MTX34 {
    typedef f32 (*MtxRef)[4];
    typedef const f32 (*MtxRefConst)[4];

    MTX34() {}

    operator MtxRef() { return mtx; }
    operator MtxRefConst() const { return mtx; }
};

struct _MTX44 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };
        f32 m[4][4];
        f32 a[16];
        Mtx44 mtx;
    };
};

struct MTX44 : public _MTX44 {
    typedef f32 (*Mtx44Ref)[4];
    typedef const f32 (*Mtx44RefConst)[4];

    MTX44() {}

    operator Mtx44Ref() { return mtx; }
    operator Mtx44RefConst() const { return mtx; }
};

MTX34* MTX34RotAxisFIdx(MTX34* out, const VEC3* axis, f32 fidx);
MTX34* MTX34RotXYZFIdx(MTX34* out, f32 fx, f32 fy, f32 fz);

inline MTX34* MTX34RotAxisRad(MTX34* out, const VEC3* axis, f32 rad) {
    return MTX34RotAxisFIdx(out, axis, 40.743664f * rad);
}

inline MTX34* MTX34RotAxisDeg(MTX34* out, const VEC3* axis, f32 deg) {
    return MTX34RotAxisFIdx(out, axis, 0.7111111f * deg);
}

inline MTX34* MTX34RotXYZRad(MTX34* out, f32 rx, f32 ry, f32 rz) {
    return MTX34RotXYZFIdx(out, 40.743664f * rx, 40.743664f * ry, 40.743664f * rz);
}

inline MTX34* MTX34RotXYZDeg(MTX34* out, f32 dx, f32 dy, f32 dz) {
    return MTX34RotXYZFIdx(out, 0.7111111f * dx, 0.7111111f * dy, 0.7111111f * dz);
}

MTX44* MTX44Identity(MTX44* out);
MTX44* MTX44Copy(MTX44* out, const MTX44* in);

}}  // namespace nw4r::math

#endif
