#define SDK_AUG2010 1
#include <tp/revolution/include/revolution/os.h>
#include <tp/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include/cmath>

#include "tp/revolution/src/kpad/__kpad.h"

typedef struct KMPLSCalibration {
    /* 0x00 */ f32 pitch_zero;
    /* 0x04 */ f32 pitch_scale;
    /* 0x08 */ f32 yaw_zero;
    /* 0x0C */ f32 yaw_scale;
    /* 0x10 */ f32 roll_zero;
    /* 0x14 */ f32 roll_scale;
    /* 0x18 */ s32 degrees;
} KMPLSCalibration;

typedef struct KMPLSChannel {
    /* 0x000 */ u32 _0[0xB8 / 4];
    /* 0x0B8 */ u8 _B8;
    /* 0x0B9 */ u8 _B9[3];
    /* 0x0BC */ u8 _BC;
    /* 0x0BD */ u8 _BD[5];
    /* 0x0C2 */ s8 _C2;
    /* 0x0C3 */ u8 _C3;
    /* 0x0C4 */ f32 _C4;
    /* 0x0C8 */ u32 _C8[4];
    /* 0x0D8 */ f32 _D8;
    /* 0x0DC */ f32 _DC;
    /* 0x0E0 */ f32 _E0;
    /* 0x0E4 */ u32 _E4[2];
    /* 0x0EC */ f32 _EC;
    /* 0x0F0 */ u32 _F0[3];
    /* 0x0FC */ f32 _FC;
    /* 0x100 */ BOOL _100;
    /* 0x104 */ f32 _104;
    /* 0x108 */ f64 scale[2][3];
    /* 0x138 */ KMPLSCalibration calib[2];
    /* 0x170 */ u32 _170[3];
    /* 0x17C */ u32 _17C;
    /* 0x180 */ s32 _180[256];
    /* 0x580 */ s32 _580[256];
    /* 0x980 */ s32 _980[256];
    /* 0xD80 */ f64 _D80[3];
    /* 0xD98 */ KPADUnifiedWpadStatus* ringBuf;
    /* 0xD9C */ KPADUnifiedWpadStatus* ringBufEx;
    /* 0xDA0 */ u32 ringBufExLen;
    /* 0xDA4 */ f32 _DA4[3];
} KMPLSChannel;

typedef struct KMPLSWork {
    /* 0x00 */ u32 _0;
    /* 0x04 */ KPADMplsSamplingCallback samplingCallback;
    /* 0x08 */ KMPLSChannel channels[WPAD_MAX_CONTROLLERS];
} KMPLSWork;

KMPLSWork* kmpls;

void WPADiGetMplsCalibration(s32 chan, KMPLSCalibration* low, KMPLSCalibration* high);
void KMPLSStartCalibration(s32 chan);

void wpad_callback_func(s32 chan, s32 result) {
    KMPLSChannel* p = &kmpls->channels[chan];

    if (kmpls == NULL) {
        return;
    }

    if (result == WPAD_ERR_NONE) {
        p->_C2 = 1;
    } else {
        p->_C2 = -1;
    }
}

static void reset_calibration(s32 chan) {
    KMPLSChannel* p = &kmpls->channels[chan];
    u32 idx;

    if (kmpls == NULL) {
        return;
    }

    idx = (p->_17C + 255) % 256;
    p->_180[idx] = p->_580[idx] = p->_980[idx] = 0x80000000;
    p->_EC = 0.0f;
}

void work_calibration(s32 chan) {
    KMPLSChannel* p = &kmpls->channels[chan];

    if (kmpls == NULL) {
        return;
    }

    if (p->_C2 == 0) {
        reset_calibration(chan);
    } else if (p->_C2 < 0) {
        p->_C2 = 0;
        WPADiControlMpls(chan, 0x80, wpad_callback_func);
    } else if (p->_EC == 1.0f) {
        if (p->_C4 <= 0.01f) {
            p->_B8 = 0;
        } else {
            p->_C2 = 0;
            WPADiControlMpls(chan, 0x80, wpad_callback_func);
            p->_C4 -= 0.01f;
            reset_calibration(chan);
        }
    }
}

BOOL KMPLSIsInit(void) {
    return kmpls != NULL;
}

void KMPLSShutdown(void) {
    kmpls = NULL;
}

void dpd_revise_scale(s32 chan) {
    f32 x = 0.0f;
    f32 y;
    f32 scale;
    f32 sx, sy;

    if (kmpls == NULL) {
        return;
    }

    if (kmpls->channels[chan]._100) {
        if (WPAD_SENSOR_BAR_POS_TOP == WPADGetSensorBarPosition()) {
            y = -0.2f;
        } else {
            y = 0.2f;
        }
    } else {
        y = -kmpls->channels[chan]._104;
    }

    sx = 1.0f;
    sy = 0.75f;
    scale = sqrt(sx * sx + sy * sy);

    if (x < 0.0f) {
        sx += x;
    } else {
        sx -= x;
    }

    if (y < 0.0f) {
        sy += y;
    } else {
        sy -= y;
    }

    kmpls->channels[chan]._FC = scale / ((sx < sy) ? sx : sy);
}

f32 move_mpls_orient(KMPLSChannel* p, Vec* a, Vec* b, Vec* c) {
    Vec d1;
    Vec d2;
    f32 len;
    f32 f;

    d1.x = a->x - b->x;
    d1.y = a->y - b->y;
    d1.z = a->z - b->z;
    len = (f32)sqrt(d1.x * d1.x + d1.y * d1.y + d1.z * d1.z);

    d2.x = a->x - c->x;
    d2.y = a->y - c->y;
    d2.z = a->z - c->z;
    if (d2.x * d1.x + d2.y * d1.y + d2.z * d1.z >= 0.0f) {
        return 0.0f;
    }

    f = a->x * d2.x + a->y * d2.y + a->z * d2.z;
    d2.x -= f * a->x;
    d2.y -= f * a->y;
    d2.z -= f * a->z;

    f = (f32)sqrt(d2.x * d2.x + d2.y * d2.y + d2.z * d2.z);
    if (f < 0.001f) {
        return 0.0f;
    }

    f = len * p->_D8 / f;
    a->x -= f * d2.x;
    a->y -= f * d2.y;
    a->z -= f * d2.z;
    return f;
}

// TODO: same instructions, about 50 of 171 in other float registers: the original keeps the length in f4 and
// 1.0f in f3 through the dead zone test and computes the three rows interleaved.
f32 revise_dir_acc(s32 chan, KPADMPDir* dir, Vec* acc) {
    KMPLSChannel* p = &kmpls->channels[chan];
    KPADMPDir m;
    KPADMPDir r;
    Vec w;
    Vec v;
    Vec n;
    f32 len;
    f32 f;
    f32 t;

    if (kmpls == NULL) {
        return 0.0f;
    }

    f = acc->x * acc->x + acc->y * acc->y + acc->z * acc->z;
    if (f == 0.0f) {
        return 0.0f;
    }

    len = (f32)sqrt(f);
    if (len < 1.0f) {
        f = 1.0f - p->_E0;
        if (len <= f) {
            return 0.0f;
        }
        f = (1.0f / p->_E0) * (len - f);
    } else {
        f = 1.0f + p->_E0;
        if (len >= f) {
            return 0.0f;
        }
        f = (-1.0f / p->_E0) * (len - f);
    }
    f *= f;
    f *= p->_DC;

    t = 1.0f / len;
    n.x = t * acc->x;
    n.y = t * acc->y;
    n.z = t * acc->z;

    w.x = n.x * dir->X.x + n.y * dir->Y.x + n.z * dir->Z.x;
    v.x = w.x + -w.x * f;
    w.y = n.x * dir->X.y + n.y * dir->Y.y + n.z * dir->Z.y;
    v.y = w.y + (-1.0f - w.y) * f;
    w.z = n.x * dir->X.z + n.y * dir->Y.z + n.z * dir->Z.z;
    v.z = w.z + -w.z * f;

    if (__KMPLS_normalize_Fxyz(&v) == 0.0f) {
        return 0.0f;
    }

    __KMPLS_make_vec_dir(&m, &w, &v);
    __KMPLS_mult_dir(&m, dir, &r);
    *dir = r;
    __KMPLS_normalize_directionXYZ(dir, 2.999f);

    w.x -= v.x;
    w.y -= v.y;
    w.z -= v.z;
    return (f32)sqrt(w.x * w.x + w.y * w.y + w.z * w.z);
}

s32 get_mpls_data_x(KMPLSChannel* p, WPADMPStatus* status) {
    f32 zero;
    f64 scale;
    f64 v;
    f64 d;
    f64 r;

    if (status->stat & 0x04) {
        zero = p->calib[1].pitch_zero;
        scale = p->scale[1][0];
    } else {
        zero = p->calib[0].pitch_zero;
        scale = p->scale[0][0];
    }

    v = scale * ((f64)status->pitch - zero);
    v -= p->_D80[0];
    d = 50.0 * v;
    if (d < 0.0) {
        d = -d;
    }
    if (d < 0.1) {
        d = 0.1;
    } else if (d > 1.0) {
        d = 1.0;
    }

    p->_D80[0] += v * d;
    r = p->_D80[0] * p->_DA4[0];
    if (r < 0.0) {
        return (s32)(r - 0.5);
    } else {
        return (s32)(0.5 + r);
    }
}

s32 get_mpls_data_y(KMPLSChannel* p, WPADMPStatus* status) {
    f32 zero;
    f64 scale;
    f64 v;
    f64 d;
    f64 r;

    if (status->stat & 0x08) {
        zero = p->calib[1].yaw_zero;
        scale = p->scale[1][1];
    } else {
        zero = p->calib[0].yaw_zero;
        scale = p->scale[0][1];
    }

    v = scale * ((f64)status->yaw - zero);
    v -= p->_D80[1];
    d = 50.0 * v;
    if (d < 0.0) {
        d = -d;
    }
    if (d < 0.1) {
        d = 0.1;
    } else if (d > 1.0) {
        d = 1.0;
    }

    p->_D80[1] += v * d;
    r = p->_D80[1] * p->_DA4[1];
    if (r < 0.0) {
        return (s32)(r - 0.5);
    } else {
        return (s32)(0.5 + r);
    }
}

s32 get_mpls_data_z(KMPLSChannel* p, WPADMPStatus* status) {
    f32 zero;
    f64 scale;
    f64 v;
    f64 d;
    f64 r;

    if (status->stat & 0x02) {
        zero = p->calib[1].roll_zero;
        scale = p->scale[1][2];
    } else {
        zero = p->calib[0].roll_zero;
        scale = p->scale[0][2];
    }

    v = scale * ((f64)status->roll - zero);
    v -= p->_D80[2];
    d = 50.0 * v;
    if (d < 0.0) {
        d = -d;
    }
    if (d < 0.1) {
        d = 0.1;
    } else if (d > 1.0) {
        d = 1.0;
    }

    p->_D80[2] += v * d;
    r = p->_D80[2] * p->_DA4[2];
    if (r < 0.0) {
        return (s32)(r - 0.5);
    } else {
        return (s32)(0.5 + r);
    }
}

void set_calibration_data(s32 chan) {
    KMPLSChannel* p = &kmpls->channels[chan];
    f64 d;

    if (kmpls == NULL) {
        return;
    }

    if (p->_BC >= 2) {
        p->scale[0][0] = 0.0;
        return;
    }

    WPADiGetMplsCalibration(chan, &p->calib[0], &p->calib[1]);
    if (p->calib[0].pitch_scale == 0.0f || p->calib[0].yaw_scale == 0.0f || p->calib[0].roll_scale == 0.0f ||
        p->calib[1].pitch_scale == 0.0f || p->calib[1].yaw_scale == 0.0f || p->calib[1].roll_scale == 0.0f) {
        p->scale[0][0] = 0.0;
        return;
    }

    d = 5242.879375 * p->calib[0].degrees;
    p->scale[0][0] = d / p->calib[0].pitch_scale;
    p->scale[0][1] = d / p->calib[0].yaw_scale;
    p->scale[0][2] = d / p->calib[0].roll_scale;

    d = 5242.879375 * p->calib[1].degrees;
    p->scale[1][0] = d / p->calib[1].pitch_scale;
    p->scale[1][1] = d / p->calib[1].yaw_scale;
    p->scale[1][2] = d / p->calib[1].roll_scale;

    p->_C2 = 1;
    KMPLSStartCalibration(chan);
}

void KMPLSSetKpadRingBuffer(s32 chan, KPADUnifiedWpadStatus* ringBuf, KPADUnifiedWpadStatus* ringBufEx, u32 ringBufExLen) {
    KMPLSChannel* p = &kmpls->channels[chan];

    if (kmpls == NULL) {
        return;
    }

    p->ringBuf = ringBuf;
    p->ringBufEx = ringBufEx;
    p->ringBufExLen = ringBufExLen;
}

void KMPLSSetSamplingCallback(KPADMplsSamplingCallback callback) {
    if (kmpls == NULL) {
        return;
    }

    kmpls->samplingCallback = callback;
}

void KMPLSStartCalibration(s32 chan) {
    KMPLSChannel* p = &kmpls->channels[chan];

    if (kmpls == NULL) {
        return;
    }

    p->_B8 = 1;
    p->_C4 = 0.03f;
    reset_calibration(chan);
}
