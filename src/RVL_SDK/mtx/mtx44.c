#include <kdc/math.h>
#include <kdc/revolution/MTX.h>

void C_MTXFrustum(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 invrange;

    invrange = 1.0f / (r - l);
    mtx[0][0] = 2.0f * n * invrange;
    mtx[0][1] = 0.0f;
    mtx[0][2] = invrange * (r + l);
    mtx[0][3] = 0.0f;

    invrange = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = 2.0f * n * invrange;
    mtx[1][2] = invrange * (t + b);
    mtx[1][3] = 0.0f;

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -n * invrange;
    mtx[2][3] = invrange * -(f * n);

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = -1.0f;
    mtx[3][3] = 0.0f;
}

void C_MTXPerspective(Mtx44 mtx, f32 fovy, f32 aspect, f32 n, f32 f) {
    f32 rad, cot;
    f32 invrange;

    rad = fovy * 0.5f;
    rad = M_PI / 180.0f * rad;
    cot = 1.0f / tanf(rad);

    mtx[0][0] = cot / aspect;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot;
    mtx[1][2] = 0.0f;
    mtx[1][3] = 0.0f;

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -n * invrange;
    mtx[2][3] = invrange * -(f * n);

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = -1.0f;
    mtx[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 invrange;

    invrange = 1.0f / (r - l);
    mtx[0][0] = 2.0f * invrange;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = invrange * -(r + l);

    invrange = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = 2.0f * invrange;
    mtx[1][2] = 0.0f;
    mtx[1][3] = invrange * -(t + b);

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f * invrange;
    mtx[2][3] = -f * invrange;

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[3][3] = 1.0f;
}

asm void PSMTX44Concat(const register Mtx44 a, const register Mtx44 b, register Mtx44 ab) {
    nofralloc
    psq_l f0, 0x0(a), 0, 0
    psq_l f2, 0x0(b), 0, 0
    ps_muls0 f6, f2, f0
    psq_l f3, 0x10(b), 0, 0
    psq_l f4, 0x20(b), 0, 0
    ps_madds1 f6, f3, f0, f6
    psq_l f1, 0x8(a), 0, 0
    psq_l f5, 0x30(b), 0, 0
    ps_madds0 f6, f4, f1, f6
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f6, f5, f1, f6
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f8, f2, f0
    ps_madds1 f8, f3, f0, f8
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f8, f4, f1, f8
    ps_madds1 f8, f5, f1, f8
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f10, f2, f0
    ps_madds1 f10, f3, f0, f10
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f10, f4, f1, f10
    ps_madds1 f10, f5, f1, f10
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f12, f2, f0
    psq_l f2, 0x8(b), 0, 0
    ps_madds1 f12, f3, f0, f12
    psq_l f0, 0x0(a), 0, 0
    ps_madds0 f12, f4, f1, f12
    psq_l f3, 0x18(b), 0, 0
    ps_madds1 f12, f5, f1, f12
    psq_l f1, 0x8(a), 0, 0
    ps_muls0 f7, f2, f0
    psq_l f4, 0x28(b), 0, 0
    ps_madds1 f7, f3, f0, f7
    psq_l f5, 0x38(b), 0, 0
    ps_madds0 f7, f4, f1, f7
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f7, f5, f1, f7
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f9, f2, f0
    psq_st f6, 0x0(ab), 0, 0
    ps_madds1 f9, f3, f0, f9
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f9, f4, f1, f9
    psq_st f8, 0x10(ab), 0, 0
    ps_madds1 f9, f5, f1, f9
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f11, f2, f0
    psq_st f10, 0x20(ab), 0, 0
    ps_madds1 f11, f3, f0, f11
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f11, f4, f1, f11
    psq_st f12, 0x30(ab), 0, 0
    ps_madds1 f11, f5, f1, f11
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f13, f2, f0
    psq_st f7, 0x8(ab), 0, 0
    ps_madds1 f13, f3, f0, f13
    psq_st f9, 0x18(ab), 0, 0
    ps_madds0 f13, f4, f1, f13
    psq_st f11, 0x28(ab), 0, 0
    ps_madds1 f13, f5, f1, f13
    psq_st f13, 0x38(ab), 0, 0
    blr
}
