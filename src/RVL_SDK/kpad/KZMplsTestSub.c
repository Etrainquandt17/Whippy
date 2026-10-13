#define SDK_AUG2010 1
#include <tp/revolution/include/revolution/os.h>
#include <tp/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include/cmath>

#include "tp/revolution/src/kpad/__kpad.h"

KPADMPDir e_dir = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};

s32 __KMPLS_f2i(f32 x) {
    if (x < 0.0f) {
        return (s32)(x - 0.5f);
    } else {
        return (s32)(0.5f + x);
    }
}

f32 __KMPLS_normalize_Fxyz(Vec* v) {
    f32 len = (f32)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    f32 f;

    if (len != 0.0f) {
        f = 1.0f / len;
        v->x *= f;
        v->y *= f;
        v->z *= f;
    }
    return len;
}

// TODO: four instructions long (223 for 219). The original keeps one scaled component of Z in f29 through the cross
// products and the other two in the registers they were loaded into; this needs f27 as well.
void __KMPLS_normalize_directionXYZ(KPADMPDir* dir, f32 limit) {
    Vec z, y, x;
    f32 len;
    f32 sum;

    do {
        len = 1.0f / (f32)sqrt(dir->X.x * dir->X.x + dir->X.y * dir->X.y + dir->X.z * dir->X.z);
        dir->X.x *= len;
        dir->X.y *= len;
        dir->X.z *= len;

        len = 1.0f / (f32)sqrt(dir->Y.x * dir->Y.x + dir->Y.y * dir->Y.y + dir->Y.z * dir->Y.z);
        dir->Y.x *= len;
        dir->Y.y *= len;
        dir->Y.z *= len;

        len = 1.0f / (f32)sqrt(dir->Z.x * dir->Z.x + dir->Z.y * dir->Z.y + dir->Z.z * dir->Z.z);
        dir->Z.x *= len;
        dir->Z.y *= len;
        dir->Z.z *= len;

        x.x = dir->Y.y * dir->Z.z - dir->Y.z * dir->Z.y;
        x.y = dir->Y.z * dir->Z.x - dir->Y.x * dir->Z.z;
        x.z = dir->Y.x * dir->Z.y - dir->Y.y * dir->Z.x;

        y.x = dir->Z.y * dir->X.z - dir->Z.z * dir->X.y;
        y.y = dir->Z.z * dir->X.x - dir->Z.x * dir->X.z;
        y.z = dir->Z.x * dir->X.y - dir->Z.y * dir->X.x;

        z.x = dir->X.y * dir->Y.z - dir->X.z * dir->Y.y;
        z.y = dir->X.z * dir->Y.x - dir->X.x * dir->Y.z;
        z.z = dir->X.x * dir->Y.y - dir->X.y * dir->Y.x;

        len = (f32)sqrt(x.x * x.x + x.y * x.y + x.z * x.z);
        sum = len;
        len = 1.0f / len;
        dir->X.x = 0.5f * (dir->X.x + len * x.x);
        dir->X.y = 0.5f * (dir->X.y + len * x.y);
        dir->X.z = 0.5f * (dir->X.z + len * x.z);

        len = (f32)sqrt(y.x * y.x + y.y * y.y + y.z * y.z);
        sum += len;
        len = 1.0f / len;
        dir->Y.x = 0.5f * (dir->Y.x + len * y.x);
        dir->Y.y = 0.5f * (dir->Y.y + len * y.y);
        dir->Y.z = 0.5f * (dir->Y.z + len * y.z);

        len = (f32)sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
        sum += len;
        len = 1.0f / len;
        dir->Z.x = 0.5f * (dir->Z.x + len * z.x);
        dir->Z.y = 0.5f * (dir->Z.y + len * z.y);
        dir->Z.z = 0.5f * (dir->Z.z + len * z.z);
    } while (sum < limit);
}

// TODO: same instructions (194), about half in other float registers and another order: the original has c.x in
// f0, c.y in f2 and c.z in f3 ahead of the square root, this has c.y in f0 and c.x in f2.
void __KMPLS_make_vec_dir(KPADMPDir* dir, Vec* v1, Vec* v2) {
    Vec c;
    Vec a;
    Vec b;
    f32 yz, zx, xy, zy, xz, yx;
    f32 len;
    f32 f;

    yz = v1->y * v2->z;
    zx = v1->z * v2->x;
    xy = v1->x * v2->y;
    zy = v1->z * v2->y;
    xz = v1->x * v2->z;
    yx = v1->y * v2->x;

    c.x = yz - zy;
    c.y = zx - xz;
    c.z = xy - yx;

    len = (f32)sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
    if (len == 0.0f) {
        *dir = e_dir;
        return;
    }

    f = 1.0f / len;
    c.x *= f;
    c.y *= f;
    c.z *= f;

    a.x = v1->y * c.z - v1->z * c.y;
    a.y = v1->z * c.x - v1->x * c.z;
    a.z = v1->x * c.y - v1->y * c.x;

    b.x = v2->y * c.z - v2->z * c.y;
    b.y = v2->z * c.x - v2->x * c.z;
    b.z = v2->x * c.y - v2->y * c.x;

    dir->X.x = c.x * c.x + b.x * a.x + v2->x * v1->x;
    dir->X.y = c.y * c.x + b.y * a.x + xy;
    dir->X.z = c.z * c.x + b.z * a.x + xz;

    dir->Y.x = c.x * c.y + b.x * a.y + yx;
    dir->Y.y = c.y * c.y + b.y * a.y + v2->y * v1->y;
    dir->Y.z = c.z * c.y + b.z * a.y + yz;

    dir->Z.x = c.x * c.z + b.x * a.z + zx;
    dir->Z.y = c.y * c.z + b.y * a.z + zy;
    dir->Z.z = c.z * c.z + b.z * a.z + v2->z * v1->z;
}

void __KMPLS_mult_dir(KPADMPDir* a, KPADMPDir* b, KPADMPDir* dst) {
    dst->X.x = b->X.x * a->X.x + b->X.y * a->Y.x + b->X.z * a->Z.x;
    dst->X.y = b->X.x * a->X.y + b->X.y * a->Y.y + b->X.z * a->Z.y;
    dst->X.z = b->X.x * a->X.z + b->X.y * a->Y.z + b->X.z * a->Z.z;

    dst->Y.x = b->Y.x * a->X.x + b->Y.y * a->Y.x + b->Y.z * a->Z.x;
    dst->Y.y = b->Y.x * a->X.y + b->Y.y * a->Y.y + b->Y.z * a->Z.y;
    dst->Y.z = b->Y.x * a->X.z + b->Y.y * a->Y.z + b->Y.z * a->Z.z;

    dst->Z.x = b->Z.x * a->X.x + b->Z.y * a->Y.x + b->Z.z * a->Z.x;
    dst->Z.y = b->Z.x * a->X.y + b->Z.y * a->Y.y + b->Z.z * a->Z.y;
    dst->Z.z = b->Z.x * a->X.z + b->Z.y * a->Y.z + b->Z.z * a->Z.z;
}

void __KMPLS_linear_Fxyz(Vec* a, Vec* b, f32 t, Vec* dst) {
    dst->x = a->x + t * (b->x - a->x);
    dst->y = a->y + t * (b->y - a->y);
    dst->z = a->z + t * (b->z - a->z);
}

void __KMPLS_linear_Direction(KPADMPDir* a, KPADMPDir* b, f32 t, KPADMPDir* dst) {
    dst->X.x = a->X.x + t * (b->X.x - a->X.x);
    dst->X.y = a->X.y + t * (b->X.y - a->X.y);
    dst->X.z = a->X.z + t * (b->X.z - a->X.z);

    dst->Y.x = a->Y.x + t * (b->Y.x - a->Y.x);
    dst->Y.y = a->Y.y + t * (b->Y.y - a->Y.y);
    dst->Y.z = a->Y.z + t * (b->Y.z - a->Y.z);

    dst->Z.x = a->Z.x + t * (b->Z.x - a->Z.x);
    dst->Z.y = a->Z.y + t * (b->Z.y - a->Z.y);
    dst->Z.z = a->Z.z + t * (b->Z.z - a->Z.z);

    __KMPLS_normalize_directionXYZ(dst, 2.999f);
}
