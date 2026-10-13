#ifndef REVOLUTION_MTX_H
#define REVOLUTION_MTX_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct Vec2 {
    f32 x;
    f32 y;
} Vec2;

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];

void PSMTXIdentity(Mtx m);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx out);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXTrans(Mtx m, f32 x, f32 y, f32 z);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void C_MTXLookAt(Mtx m, const Vec* pos, const Vec* up, const Vec* target);

void C_MTXFrustum(Mtx44 m, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
void C_MTXOrtho(Mtx44 m, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
void C_MTXPerspective(Mtx44 m, f32 fovy, f32 aspect, f32 near, f32 far);
void PSMTX44Concat(const Mtx44 a, const Mtx44 b, Mtx44 out);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);

#ifdef __cplusplus
}
#endif

#endif
