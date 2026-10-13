#define SDK_AUG2010 1
#include <tp/revolution/include/revolution/os.h>
#include <tp/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include/cmath>
#include <tp/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include/cstring>

#include "tp/revolution/src/kpad/__kpad.h"

static const char* __KPADVersion = "<< RVL_SDK - KPAD \trelease build: Dec 11 2009 15:58:25 (0x4302_145) >>";

static Vec2 icenter_org = {0.000f, 0.000f};
static f32 idist_org = 1.000f;
static Vec2 iaccXY_nrm_hori = {0.000f, -1.000f};
static Vec2 isec_nrm_hori = {1.000f, 0.000f};
f32 kp_obj_interval = 0.200f;

f32 kp_acc_horizon_pw = 0.050f;
f32 kp_ah_circle_radius = 0.070f;
f32 kp_ah_circle_pw = 0.060f;
u16 kp_ah_circle_ct = 100;
BOOL kp_stick_clamp_cross = FALSE;

f32 kp_err_outside_frame = 0.050f;
f32 kp_err_dist_min;
f32 kp_err_dist_max = 3.000f;
f32 kp_err_dist_speed = 0.040f;
f32 kp_err_first_inpr = 0.900f;
f32 kp_err_next_inpr = 0.900f;
f32 kp_err_acc_inpr = 0.900f;
f32 kp_err_up_inpr = 0.700f;
f32 kp_err_near_pos = 0.100f;

static f32 kp_dist_vv1;

static s32 kp_fs_fstick_min = 15;
static s32 kp_fs_fstick_max = 71;
static s32 kp_cl_stick_min = 60;
static s32 kp_cl_stick_max = 308;
static s32 kp_cl_trigger_min = 30;
static s32 kp_cl_trigger_max = 180;
static f32 kp_rm_acc_max = 3.4f;
static f32 kp_fs_acc_max = 2.1f;
static s32 kp_ex_trigger_min = 0;
static s32 kp_ex_trigger_max = 256;
static s32 kp_ex_analog_min = 0;
static s32 kp_ex_analog_max = 1024;

static u8 kp_initialized = FALSE;

KPADInsideStatus inside_kpads[WPAD_MAX_CONTROLLERS];
static Vec2 Vec2_0 = {0.0f, 0.0f};
static Mtx kp_fs_rot;

static f64 kp_wbc_ave_sample[4];
static f64 kp_wbc_weight_ave[4];
static f64 kp_wbc_max_weight = 0.0;
static f64 kp_wbc_min_weight = 0.0;
static f64 kp_wbc_tgc_weight = 0.0;
static f32 kp_wbc_ave_count = 400.0f;
static u16 kp_wbc_ave_sample_count = 0;
static u8 kp_wbc_calib_count = 200;
static u8 kp_wbc_failure_count = 0;
static s8 kp_wbc_zero_point_done = 0;
static u8 kp_wbc_zero_point_wait = 0;
static u8 kp_wbc_tgc_weight_done = 0;
static s16 kp_wbc_tgc_weight_wait = 0;
static s8 kp_wbc_tgc_weight_err = 0;
static s8 kp_wbc_enabled = FALSE;
static u8 kp_wbc_issued = FALSE;

// Only the unused KPADSetConfig refers to it, so it is global here to stay in the object.
u32 kp_config[4];
static f32 kp_fs_revise_deg = 24.0f;

static void KPADiSamplingCallback(s32 chan);
static void KPADiConnectCallback(s32 chan, s32 result);
static void KPADiControlDpdCallback(s32 chan, s32 result);
static void KPADiControlMplsCallback(s32 chan, s32 result);

void KPADSetBtnRepeat(s32 chan, f32 delay_sec, f32 pulse_sec) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    if (pulse_sec) {
        kp->btn_repeat_delay = (u16)(s32)(delay_sec * 200.0f + 0.5f);
        kp->btn_repeat_pulse = (u16)(s32)(pulse_sec * 200.0f + 0.5f);
    } else {
        kp->btn_repeat_delay = KPAD_BTN_NO_RPT_DELAY;
        kp->btn_repeat_pulse = 0;
    }

    kp->btn_repeat_time = 0;
    kp->btn_repeat_next = kp->btn_repeat_delay;
    kp->btn_cl_repeat_time = 0;
    kp->btn_cl_repeat_next = kp->btn_repeat_delay;
}

void KPADSetObjInterval(f32 interval) {
}

void KPADSetPosParam(s32 chan, f32 play_radius, f32 sensitivity) {
    inside_kpads[chan].pos_play_radius = play_radius;
    inside_kpads[chan].pos_sensitivity = sensitivity;
}

void KPADSetHoriParam(s32 chan, f32 play_radius, f32 sensitivity) {
    inside_kpads[chan].hori_play_radius = play_radius;
    inside_kpads[chan].hori_sensitivity = sensitivity;
}

void KPADSetDistParam(s32 chan, f32 play_radius, f32 sensitivity) {
    inside_kpads[chan].dist_play_radius = play_radius;
    inside_kpads[chan].dist_sensitivity = sensitivity;
}

void KPADSetAccParam(s32 chan, f32 play_radius, f32 sensitivity) {
    inside_kpads[chan].acc_play_radius = play_radius;
    inside_kpads[chan].acc_sensitivity = sensitivity;
}

void KPADGetPosParam(s32 chan, f32* play_radius, f32* sensitivity) {
    *play_radius = inside_kpads[chan].pos_play_radius;
    *sensitivity = inside_kpads[chan].pos_sensitivity;
}

void KPADGetHoriParam(s32 chan, f32* play_radius, f32* sensitivity) {
    *play_radius = inside_kpads[chan].hori_play_radius;
    *sensitivity = inside_kpads[chan].hori_sensitivity;
}

void KPADGetDistParam(s32 chan, f32* play_radius, f32* sensitivity) {
    *play_radius = inside_kpads[chan].dist_play_radius;
    *sensitivity = inside_kpads[chan].dist_sensitivity;
}

void KPADGetAccParam(s32 chan, f32* play_radius, f32* sensitivity) {
    *play_radius = inside_kpads[chan].acc_play_radius;
    *sensitivity = inside_kpads[chan].acc_sensitivity;
}

static void calc_dpd2pos_scale(KPADInsideStatus* kp) {
    f32 scale;
    f32 sx, sy;
    sx = 1.0f;
    sy = (f32)KPAD_DPD_RESO_WY / (f32)KPAD_DPD_RESO_WX;

    scale = sqrt(sx * sx + sy * sy);

    if (kp->center_org.x < 0.0f) {
        sx += kp->center_org.x;
    } else {
        sx -= kp->center_org.x;
    }

    if (kp->center_org.y < 0.0f) {
        sy += kp->center_org.y;
    } else {
        sy -= kp->center_org.y;
    }

    kp->dpd2pos_scale = scale / ((sx < sy) ? sx : sy);
}

void reset_kpad(s32 chan) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    KPADObject* op;
    KPADStatus* sp = &kp->status;

    kp->resetReq = FALSE;

    kp->kobj_frame_min.x = -1.0f + kp_err_outside_frame;
    kp->kobj_frame_max.x = 1.0f - kp_err_outside_frame;
    kp->kobj_frame_min.y = -((f32)KPAD_DPD_RESO_WY / KPAD_DPD_RESO_WX) + kp_err_outside_frame;
    kp->kobj_frame_max.y = ((f32)KPAD_DPD_RESO_WY / KPAD_DPD_RESO_WX) - kp_err_outside_frame;

    kp->err_dist_speed_1 = 1.0f / kp_err_dist_speed;
    kp->err_dist_speedM_1 = -1.0f / kp_err_dist_speed;
    kp->ah_circle_radius2 = kp_ah_circle_radius * kp_ah_circle_radius;

    kp->err_dist_min = kp_err_dist_min;
    kp->dist_vv1 = kp_dist_vv1;

    sp->hold = sp->trig = sp->release = 0;
    kp->btn_repeat_time = 0;
    kp->btn_repeat_next = kp->btn_repeat_delay;

    sp->dpd_valid_fg = 0;
    kp->dpd_valid2_ct = 0;

    sp->pos = sp->vec = Vec2_0;
    sp->speed = 0.0f;

    sp->horizon.x = kp->acc_horizon.x = kp->obj_horizon.x = 1.0f;
    sp->horizon.y = kp->acc_horizon.y = kp->obj_horizon.y = 0.0f;
    sp->hori_vec = Vec2_0;
    sp->hori_speed = 0.0f;

    sp->acc_vertical.x = 1.0f;
    sp->acc_vertical.y = 0.0f;

    sp->dist = kp->dist_org;
    sp->dist_vec = sp->dist_speed = 0.0f;

    kp->sec_dist = sp->dist;
    kp->sec_length = kp->trust_sec_length = kp->dist_vv1 / kp->sec_dist;
    kp->sec_nrm = kp->sec_nrm_hori;

    sp->acc.x = sp->acc.z = 0.0f;
    sp->acc.y = -1.0f;
    sp->acc_value = 1.0f;
    sp->acc_speed = 0.0f;
    kp->hard_acc = sp->acc;

    kp->ah_circle_pos = kp->acc_horizon;
    kp->ah_circle_ct = kp_ah_circle_ct;

    kp->valid_objs = 0;

    op = &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1];
    do {
        op->error_fg = -1;
    } while (--op >= kp->kobj_sample);

    op = &kp->kobj_regular[KPAD_USE_OBJECTS - 1];
    do {
        op->error_fg = -1;
    } while (--op >= kp->kobj_regular);

    kp->bufCount = 0;
    kp->exResetReq = TRUE;
}

void KPADEnableAimingMode(s32 chan) {
    inside_kpads[chan].aimReq = TRUE;
    inside_kpads[chan].aimEnabled = TRUE;
}

void KPADDisableAimingMode(s32 chan) {
    inside_kpads[chan].aimReq = TRUE;
    inside_kpads[chan].aimEnabled = FALSE;
}

u8 KPADIsEnableAimingMode(s32 chan) {
    return inside_kpads[chan].aimEnabled;
}

void KPADSetSensorHeight(s32 chan, f32 level) {
    KPADInsideStatus* kp = &inside_kpads[chan];

    kp->center_org.x = 0.0f;
    kp->center_org.y = -level;
    calc_dpd2pos_scale(kp);
}

f32 KPADGetSensorHeight(s32 chan) {
    return inside_kpads[chan].center_org.y;
}

#define IS_CLASSIC_FAMILY(dev_type)                                                                                    \
    (((dev_type) >= WPAD_DEV_TRAIN && (dev_type) <= WPAD_DEV_TAIKO) || (dev_type) == WPAD_DEV_CLASSIC ||               \
     (dev_type) == WPAD_DEV_MPLS_CLASSIC)

void calc_button_repeat(KPADInsideStatus* kp, u32 dev_type, u32 count) {
    KPADStatus* sp = &kp->status;
    KPADEXStatus* ep = &kp->status.ex_status;

    if (sp->trig != 0 || sp->release != 0) {
        kp->btn_repeat_time = 0;
        kp->btn_repeat_next = kp->btn_repeat_delay;
        if (sp->trig && kp->btn_repeat_pulse) {
            sp->hold |= KPAD_BUTTON_RPT;
        }
    } else if (sp->hold != 0) {
        kp->btn_repeat_time += count;
        if (kp->btn_repeat_time >= KPAD_BTN_NO_RPT_DELAY) {
            kp->btn_repeat_time -= KPAD_BTN_NO_RPT_DELAY;
        }

        if (kp->btn_repeat_time >= kp->btn_repeat_next) {
            sp->hold |= KPAD_BUTTON_RPT;
            kp->btn_repeat_next += kp->btn_repeat_pulse;
            if (kp->btn_repeat_time >= KPAD_BTN_RPT_TIME_MAX) {
                kp->btn_repeat_time -= KPAD_BTN_RPT_TIME_MAX;
                kp->btn_repeat_next -= KPAD_BTN_RPT_TIME_MAX;
            }
        }
    }

    if (IS_CLASSIC_FAMILY(dev_type)) {
        if (ep->cl.trig != 0 || ep->cl.release != 0) {
            kp->btn_cl_repeat_time = 0;
            kp->btn_cl_repeat_next = kp->btn_repeat_delay;
            if (ep->cl.trig && kp->btn_repeat_pulse) {
                ep->cl.hold |= KPAD_BUTTON_RPT;
            }
        } else if (ep->cl.hold != 0) {
            kp->btn_cl_repeat_time += count;
            if (kp->btn_cl_repeat_time >= KPAD_BTN_NO_RPT_DELAY) {
                kp->btn_cl_repeat_time -= KPAD_BTN_NO_RPT_DELAY;
            }

            if (kp->btn_cl_repeat_time >= kp->btn_cl_repeat_next) {
                ep->cl.hold |= KPAD_BUTTON_RPT;
                kp->btn_cl_repeat_next += kp->btn_repeat_pulse;
                if (kp->btn_cl_repeat_time >= KPAD_BTN_RPT_TIME_MAX) {
                    kp->btn_cl_repeat_time -= KPAD_BTN_RPT_TIME_MAX;
                    kp->btn_cl_repeat_next -= KPAD_BTN_RPT_TIME_MAX;
                }
            }
        }
    }
}

void read_kpad_button(KPADInsideStatus* kp, u32 dev_type, u32 count, u32 core, u32 fs, u32 cl) {
    KPADStatus* sp = &kp->status;
    KPADEXStatus* ep = &kp->status.ex_status;
    u32 old_fg, change_fg;
    u32 cl_old_fg, cl_change_fg;

    old_fg = sp->hold & KPAD_BUTTON_MASK;
    sp->hold = core & (KPAD_BUTTON_MASK & ~(WPAD_BUTTON_Z | WPAD_BUTTON_C));
    if (dev_type == WPAD_DEV_FREESTYLE || dev_type == WPAD_DEV_MPLS_FREESTYLE) {
        sp->hold |= (kp->exResetReq ? 0 : fs) & (WPAD_BUTTON_Z | WPAD_BUTTON_C);
    }
    change_fg = sp->hold ^ old_fg;
    sp->trig = change_fg & sp->hold;
    sp->release = change_fg & old_fg;

    if (IS_CLASSIC_FAMILY(dev_type)) {
        cl = kp->exResetReq ? 0 : cl;
        cl_old_fg = ep->cl.hold & KPAD_BUTTON_MASK;
        ep->cl.hold = cl & KPAD_BUTTON_MASK;
        cl_change_fg = ep->cl.hold ^ cl_old_fg;
        ep->cl.trig = cl_change_fg & ep->cl.hold;
        ep->cl.release = cl_change_fg & cl_old_fg;
    }

    calc_button_repeat(kp, dev_type, count);
}

void calc_acc(KPADInsideStatus* kp, f32* acc, f32 acc2) {
    f32 f1, f2;

    f2 = acc2 - *acc;

    if (kp->acc_play_mode == KPAD_PLAY_MODE_LOOSE) {
        if (f2 < 0.0f) {
            f1 = -f2;
        } else {
            f1 = f2;
        }

        if (f1 >= kp->acc_play_radius) {
            f1 = 1.0f;
        } else {
            f1 /= kp->acc_play_radius;
            f1 *= f1;
            f1 *= f1;
        }
        f1 *= kp->acc_sensitivity;
        *acc += f1 * f2;
    } else {
        if (f2 < -kp->acc_play_radius) {
            *acc += (f2 + kp->acc_play_radius) * kp->acc_sensitivity;
        } else if (f2 > kp->acc_play_radius) {
            *acc += (f2 - kp->acc_play_radius) * kp->acc_sensitivity;
        }
    }
}

void calc_acc_horizon(KPADInsideStatus* kp) {
    f32 f1, vx, vy, ax, ay;
    f1 = sqrt(kp->hard_acc.x * kp->hard_acc.x + kp->hard_acc.y * kp->hard_acc.y);
    if (f1 == 0.0f || f1 >= 2.0f) {
        return;
    }
    ax = kp->hard_acc.x / f1;
    ay = kp->hard_acc.y / f1;

    if (f1 > 1.0f) {
        f1 = 2.0f - f1;
    }
    f1 *= f1 * kp_acc_horizon_pw;

    vx = kp->accXY_nrm_hori.x * ax + kp->accXY_nrm_hori.y * ay;
    vy = kp->accXY_nrm_hori.y * ax - kp->accXY_nrm_hori.x * ay;
    ax = (vx - kp->acc_horizon.x) * f1 + kp->acc_horizon.x;
    ay = (vy - kp->acc_horizon.y) * f1 + kp->acc_horizon.y;

    f1 = sqrt(ax * ax + ay * ay);
    if (f1 == 0.0f) {
        return;
    }
    kp->acc_horizon.x = ax / f1;
    kp->acc_horizon.y = ay / f1;

    kp->ah_circle_pos.x += (kp->acc_horizon.x - kp->ah_circle_pos.x) * kp_ah_circle_pw;
    kp->ah_circle_pos.y += (kp->acc_horizon.y - kp->ah_circle_pos.y) * kp_ah_circle_pw;

    vx = kp->acc_horizon.x - kp->ah_circle_pos.x;
    vy = kp->acc_horizon.y - kp->ah_circle_pos.y;
    if (vx * vx + vy * vy <= kp->ah_circle_radius2) {
        if (kp->ah_circle_ct)
            --kp->ah_circle_ct;
    } else {
        kp->ah_circle_ct = kp_ah_circle_ct;
    }
}

static void clamp_trigger(f32* trigger, s32 tr, s32 min, s32 max) {
    if (tr <= min) {
        *trigger = 0.0f;
    } else if (tr >= max) {
        *trigger = 1.0f;
    } else {
        *trigger = (f32)(tr - min) / (f32)(max - min);
    }
}

void calc_acc_vertical(KPADInsideStatus* kp) {
    KPADStatus* sp = &kp->status;
    f32 f1, f2, ax, ay;

    ax = sqrt(f2 = kp->hard_acc.x * kp->hard_acc.x + kp->hard_acc.y * kp->hard_acc.y);
    ay = -kp->hard_acc.z;
    f1 = sqrt(f2 + ay * ay);
    if (f1 == 0.0f || f1 >= 2.0f) {
        return;
    }
    f2 = ax / f1;
    ay /= f1;

    if (f1 > 1.0f) {
        f1 = 2.0f - f1;
    }
    f1 *= f1 * kp_acc_horizon_pw;

    ax = (f2 - sp->acc_vertical.x) * f1 + sp->acc_vertical.x;
    ay = (ay - sp->acc_vertical.y) * f1 + sp->acc_vertical.y;

    f1 = sqrt(ax * ax + ay * ay);
    if (f1 == 0.0f) {
        return;
    }
    sp->acc_vertical.x = ax / f1;
    sp->acc_vertical.y = ay / f1;
}

static f32 clamp_acc(f32 acc, f32 clamp) {
    if (acc < 0.0f) {
        if (acc < -clamp)
            return -clamp;
    } else {
        if (acc > clamp)
            return clamp;
    }
    return acc;
}

void read_kpad_acc(KPADInsideStatus* kp, KPADUnifiedWpadStatus* uwp) {
    KPADStatus* sp = &kp->status;
    Vec fsrc;
    Vec vec;
    Vec fsvec;

    switch (uwp->fmt) {
    case WPAD_FMT_CORE_ACC:
    case WPAD_FMT_CORE_ACC_DPD:
    case WPAD_FMT_FREESTYLE_ACC:
    case WPAD_FMT_FREESTYLE_ACC_DPD:
    case WPAD_FMT_CLASSIC_ACC:
    case WPAD_FMT_CLASSIC_ACC_DPD:
    case WPAD_FMT_GUITAR:
    case WPAD_FMT_DRUM:
    case WPAD_FMT_MOTION_PLUS:
    case WPAD_FMT_TAIKO:
    case WPAD_FMT_BULK:
        break;

    default:
        return;
    }

    kp->hard_acc.x = clamp_acc((f32)(s32)-uwp->u.core.accX * kp->acc_scale_x, kp_rm_acc_max);
    kp->hard_acc.y = clamp_acc((f32)(s32)-uwp->u.core.accZ * kp->acc_scale_z, kp_rm_acc_max);
    kp->hard_acc.z = clamp_acc((f32)(s32)uwp->u.core.accY * kp->acc_scale_y, kp_rm_acc_max);

    vec = sp->acc;

    calc_acc(kp, &sp->acc.x, kp->hard_acc.x);
    calc_acc(kp, &sp->acc.y, kp->hard_acc.y);
    calc_acc(kp, &sp->acc.z, kp->hard_acc.z);
    sp->acc_value = sqrt(sp->acc.x * sp->acc.x + sp->acc.y * sp->acc.y + sp->acc.z * sp->acc.z);

    vec.x -= sp->acc.x;
    vec.y -= sp->acc.y;
    vec.z -= sp->acc.z;
    sp->acc_speed = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    calc_acc_horizon(kp);
    calc_acc_vertical(kp);

    if ((uwp->u.core.err == WPAD_ERR_NONE && uwp->u.core.dev == WPAD_DEV_FREESTYLE &&
         (uwp->fmt == WPAD_FMT_FREESTYLE_ACC || uwp->fmt == WPAD_FMT_FREESTYLE_ACC_DPD)) ||
        (uwp->u.core.dev == WPAD_DEV_MPLS_FREESTYLE && uwp->fmt == WPAD_FMT_MOTION_PLUS && (uwp->u.mp.stat & 0x40))) {
        if (uwp->u.core.dev == WPAD_DEV_FREESTYLE) {
            fsrc.x = clamp_acc((f32)(s32)-uwp->u.fs.fsAccX * kp->fs_acc_scale_x, kp_fs_acc_max);
            fsrc.y = clamp_acc((f32)(s32)-uwp->u.fs.fsAccZ * kp->fs_acc_scale_z, kp_fs_acc_max);
            fsrc.z = clamp_acc((f32)(s32)uwp->u.fs.fsAccY * kp->fs_acc_scale_y, kp_fs_acc_max);
        } else {
            fsrc.x = clamp_acc((f32)(s32)-uwp->u.mp.ext.fs.fsAccX * kp->fs_acc_scale_x, kp_fs_acc_max);
            fsrc.y = clamp_acc((f32)(s32)-uwp->u.mp.ext.fs.fsAccZ * kp->fs_acc_scale_z, kp_fs_acc_max);
            fsrc.z = clamp_acc((f32)(s32)uwp->u.mp.ext.fs.fsAccY * kp->fs_acc_scale_y, kp_fs_acc_max);
        }

        if (kp->fsAccRevise) {
            PSMTXMultVec(kp_fs_rot, &fsrc, &fsrc);
        }

        fsvec = sp->ex_status.fs.acc;

        calc_acc(kp, &sp->ex_status.fs.acc.x, fsrc.x);
        calc_acc(kp, &sp->ex_status.fs.acc.y, fsrc.y);
        calc_acc(kp, &sp->ex_status.fs.acc.z, fsrc.z);
        sp->ex_status.fs.acc_value = sqrt(sp->ex_status.fs.acc.x * sp->ex_status.fs.acc.x + sp->ex_status.fs.acc.y * sp->ex_status.fs.acc.y +
                                          sp->ex_status.fs.acc.z * sp->ex_status.fs.acc.z);

        fsvec.x -= sp->ex_status.fs.acc.x;
        fsvec.y -= sp->ex_status.fs.acc.y;
        fsvec.z -= sp->ex_status.fs.acc.z;
        sp->ex_status.fs.acc_speed = sqrt(fsvec.x * fsvec.x + fsvec.y * fsvec.y + fsvec.z * fsvec.z);
    }
}

static f32 calc_horizon(KPADInsideStatus* kp, Vec2* p1, Vec2* p2, Vec2* hori) {
    f32 f1, f2, vx, vy;

    vx = p2->x - p1->x;
    vy = p2->y - p1->y;
    f2 = sqrt(vx * vx + vy * vy);
    f1 = 1.0f / f2;
    vx *= f1;
    vy *= f1;

    hori->x = kp->sec_nrm_hori.x * vx + kp->sec_nrm_hori.y * vy;
    hori->y = kp->sec_nrm_hori.y * vx - kp->sec_nrm_hori.x * vy;

    return kp->dist_vv1 * f1;
}

s8 select_2obj_first(KPADInsideStatus* kp) {
    KPADObject *op1, *op2, *rp1, *rp2;
    Vec2 hori;
    f32 f1, max = kp_err_first_inpr;

    op1 = kp->kobj_sample;
    do {
        if (op1->error_fg != 0) {
            continue;
        }

        op2 = op1 + 1;
        do {
            if (op2->error_fg != 0) {
                continue;
            }

            f1 = calc_horizon(kp, &op1->center, &op2->center, &hori);

            if (f1 <= kp->err_dist_min || f1 >= kp_err_dist_max) {
                continue;
            }

            f1 = kp->acc_horizon.x * hori.x + kp->acc_horizon.y * hori.y;
            if (f1 < 0.0f) {
                if (-f1 > max) {
                    max = -f1;
                    rp1 = op2;
                    rp2 = op1;
                }
            } else {
                if (f1 > max) {
                    max = f1;
                    rp1 = op1;
                    rp2 = op2;
                }
            }

        } while (++op2 <= &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1]);
    } while (++op1 < &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1]);

    if (max == kp_err_first_inpr) {
        return 0;
    }

    kp->kobj_regular[0] = *rp1;
    kp->kobj_regular[1] = *rp2;

    return 2;
}

s8 select_2obj_continue(KPADInsideStatus* kp) {
    KPADObject *op1, *op2, *rp1, *rp2;
    Vec2 nrm;
    s32 rev_fg;
    f32 f1, f2, f3, vx, vy, min = 2.0f;
    op1 = kp->kobj_sample;
    do {
        if (op1->error_fg != 0) {
            continue;
        }

        op2 = op1 + 1;
        do {
            if (op2->error_fg != 0) {
                continue;
            }
            vx = op2->center.x - op1->center.x;
            vy = op2->center.y - op1->center.y;
            f3 = sqrt(vx * vx + vy * vy);
            f1 = 1.0f / f3;
            nrm.x = vx * f1;
            nrm.y = vy * f1;

            f1 *= kp->dist_vv1;
            if (f1 <= kp->err_dist_min || f1 >= kp_err_dist_max) {
                continue;
            }

            f1 -= kp->sec_dist;
            if (f1 < 0.0f) {
                f1 *= kp->err_dist_speedM_1;
            } else {
                f1 *= kp->err_dist_speed_1;
            }
            if (f1 >= 1.0f) {
                continue;
            }

            f2 = kp->sec_nrm.x * nrm.x + kp->sec_nrm.y * nrm.y;
            if (f2 < 0.0f) {
                f2 = -f2;
                rev_fg = 1;
            } else {
                rev_fg = 0;
            }
            if (f2 <= kp_err_next_inpr) {
                continue;
            }
            f2 = (1.0f - f2) / (1.0f - kp_err_next_inpr);
            f1 += f2;
            if (f1 < min) {
                min = f1;
                if (rev_fg) {
                    rp1 = op2;
                    rp2 = op1;
                } else {
                    rp1 = op1;
                    rp2 = op2;
                }
            }

        } while (++op2 <= &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1]);
    } while (++op1 < &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1]);

    if (min == 2.0f) {
        return 0;
    }

    kp->kobj_regular[0] = *rp1;
    kp->kobj_regular[1] = *rp2;

    return 2;
}

s8 select_1obj_first(KPADInsideStatus* kp) {
    KPADObject* op1;
    f32 vx, vy;
    Vec2 p1, p2;

    vx = kp->sec_nrm_hori.x * kp->acc_horizon.x + kp->sec_nrm_hori.y * kp->acc_horizon.y;
    vy = kp->sec_nrm_hori.y * kp->acc_horizon.x - kp->sec_nrm_hori.x * kp->acc_horizon.y;

    vx *= kp->trust_sec_length;
    vy *= kp->trust_sec_length;

    op1 = kp->kobj_sample;
    do {
        if (op1->error_fg != 0) {
            continue;
        }

        p1.x = op1->center.x - vx;
        p1.y = op1->center.y - vy;
        p2.x = op1->center.x + vx;
        p2.y = op1->center.y + vy;

        if (p1.x <= kp->kobj_frame_min.x || p1.x >= kp->kobj_frame_max.x || p1.y <= kp->kobj_frame_min.y || p1.y >= kp->kobj_frame_max.y) {
            if (p2.x > kp->kobj_frame_min.x && p2.x < kp->kobj_frame_max.x && p2.y > kp->kobj_frame_min.y && p2.y < kp->kobj_frame_max.y) {
                kp->kobj_regular[1] = *op1;
                kp->kobj_regular[0].center = p1;
                kp->kobj_regular[0].error_fg = 0;
                kp->kobj_regular[0].state_fg = -1;

                return -1;
            }
        } else {
            if (p2.x <= kp->kobj_frame_min.x || p2.x >= kp->kobj_frame_max.x || p2.y <= kp->kobj_frame_min.y || p2.y >= kp->kobj_frame_max.y) {
                kp->kobj_regular[0] = *op1;

                kp->kobj_regular[1].center = p2;
                kp->kobj_regular[1].error_fg = 0;
                kp->kobj_regular[1].state_fg = -1;

                return -1;
            }
        }

    } while (++op1 < &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS]);

    return 0;
}

s8 select_1obj_continue(KPADInsideStatus* kp) {
    KPADObject *op1, *op2, *rp1, *rp2;
    f32 f1, vx, vy;
    f32 min = kp_err_near_pos * kp_err_near_pos;

    op1 = kp->kobj_regular;
    do {
        if (op1->error_fg != 0) {
            continue;
        }
        if (op1->state_fg != 0) {
            continue;
        }

        op2 = kp->kobj_sample;
        do {
            if (op2->error_fg != 0) {
                continue;
            }

            vx = op1->center.x - op2->center.x;
            vy = op1->center.y - op2->center.y;
            f1 = vx * vx + vy * vy;
            if (f1 < min) {
                min = f1;
                rp1 = op1;
                rp2 = op2;
            }
        } while (++op2 < &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS]);
    } while (++op1 < &kp->kobj_regular[KPAD_USE_OBJECTS]);

    if (min == kp_err_near_pos * kp_err_near_pos)
        return 0;

    *rp1 = *rp2;
    kp->sec_nrm.x = kp->sec_nrm_hori.x * kp->acc_horizon.x + kp->sec_nrm_hori.y * kp->acc_horizon.y;
    kp->sec_nrm.y = kp->sec_nrm_hori.y * kp->acc_horizon.x - kp->sec_nrm_hori.x * kp->acc_horizon.y;

    vx = kp->sec_length * kp->sec_nrm.x;
    vy = kp->sec_length * kp->sec_nrm.y;
    if (rp1 == &kp->kobj_regular[0]) {
        kp->kobj_regular[1].center.x = rp1->center.x + vx;
        kp->kobj_regular[1].center.y = rp1->center.y + vy;
        kp->kobj_regular[1].error_fg = 0;
        kp->kobj_regular[1].state_fg = -1;
    } else {
        kp->kobj_regular[0].center.x = rp1->center.x - vx;
        kp->kobj_regular[0].center.y = rp1->center.y - vy;
        kp->kobj_regular[0].error_fg = 0;
        kp->kobj_regular[0].state_fg = -1;
    }

    if (kp->status.dpd_valid_fg < 0) {
        return -1;
    } else {
        return 1;
    }
}

void calc_dpd_variable(KPADInsideStatus* kp, s8 valid_fg_next) {
    KPADStatus* sp = &kp->status;
    f32 f1, f2, dist;
    Vec2 pos, vec;

    if (valid_fg_next == 0) {
        sp->dpd_valid_fg = 0;
        return;
    }

    pos.x = kp->sec_nrm_hori.x * kp->sec_nrm.x + kp->sec_nrm_hori.y * kp->sec_nrm.y;
    pos.y = kp->sec_nrm_hori.y * kp->sec_nrm.x - kp->sec_nrm_hori.x * kp->sec_nrm.y;

    if (sp->dpd_valid_fg == 0) {
        sp->horizon = pos;
        sp->hori_vec = Vec2_0;
        sp->hori_speed = 0.0f;
    } else {
        vec.x = pos.x - sp->horizon.x;
        vec.y = pos.y - sp->horizon.y;
        f1 = sqrt(vec.x * vec.x + vec.y * vec.y);

        if (kp->hori_play_mode == KPAD_PLAY_MODE_LOOSE) {
            if (f1 >= kp->hori_play_radius) {
                f2 = 1.0f;
            } else {
                f2 = f1 / kp->hori_play_radius;
                f2 *= f2;
                f2 *= f2;
            }
            f2 *= kp->hori_sensitivity;
            vec.x = f2 * vec.x + sp->horizon.x;
            vec.y = f2 * vec.y + sp->horizon.y;
            f1 = sqrt(vec.x * vec.x + vec.y * vec.y);
            vec.x /= f1;
            vec.y /= f1;

            sp->hori_vec.x = vec.x - sp->horizon.x;
            sp->hori_vec.y = vec.y - sp->horizon.y;
            sp->hori_speed = sqrt(sp->hori_vec.x * sp->hori_vec.x + sp->hori_vec.y * sp->hori_vec.y);

            sp->horizon = vec;
        } else {
            if (f1 > kp->hori_play_radius) {
                f1 = (f1 - kp->hori_play_radius) / f1 * kp->hori_sensitivity;
                vec.x = vec.x * f1 + sp->horizon.x;
                vec.y = vec.y * f1 + sp->horizon.y;
                f1 = sqrt(vec.x * vec.x + vec.y * vec.y);
                vec.x /= f1;
                vec.y /= f1;

                sp->hori_vec.x = vec.x - sp->horizon.x;
                sp->hori_vec.y = vec.y - sp->horizon.y;
                sp->hori_speed = sqrt(sp->hori_vec.x * sp->hori_vec.x + sp->hori_vec.y * sp->hori_vec.y);

                sp->horizon = vec;
            } else {
                sp->hori_vec = Vec2_0;
                sp->hori_speed = 0.0f;
            }
        }
    }

    dist = kp->dist_vv1 / kp->sec_length;

    if (sp->dpd_valid_fg == 0) {
        sp->dist = dist;
        sp->dist_vec = 0.0f;
        sp->dist_speed = 0.0f;
    } else {
        f2 = dist - sp->dist;
        if (f2 < 0.0f) {
            f1 = -f2;
        } else {
            f1 = f2;
        }

        if (kp->dist_play_mode == KPAD_PLAY_MODE_LOOSE) {
            if (f1 >= kp->dist_play_radius) {
                f1 = 1.0f;
            } else {
                f1 /= kp->dist_play_radius;
                f1 *= f1;
                f1 *= f1;
            }
            f1 *= kp->dist_sensitivity;

            sp->dist_vec = f1 * f2;
            if (sp->dist_vec < 0.0f) {
                sp->dist_speed = -sp->dist_vec;
            } else {
                sp->dist_speed = sp->dist_vec;
            }

            sp->dist += sp->dist_vec;
        } else {
            if (f1 > kp->dist_play_radius) {
                f1 = (f1 - kp->dist_play_radius) / f1 * kp->dist_sensitivity;
                sp->dist_vec = f1 * f2;
                if (sp->dist_vec < 0.0f) {
                    sp->dist_speed = -sp->dist_vec;
                } else {
                    sp->dist_speed = sp->dist_vec;
                }

                sp->dist += sp->dist_vec;
            } else {
                sp->dist_vec = 0.0f;
                sp->dist_speed = 0.0f;
            }
        }
    }

    pos.x = (kp->kobj_regular[0].center.x + kp->kobj_regular[1].center.x) * 0.5f;
    pos.y = (kp->kobj_regular[0].center.y + kp->kobj_regular[1].center.y) * 0.5f;

    f1 = kp->sec_nrm.x * kp->sec_nrm_hori.x + kp->sec_nrm.y * kp->sec_nrm_hori.y;
    f2 = -kp->sec_nrm.y * kp->sec_nrm_hori.x + kp->sec_nrm.x * kp->sec_nrm_hori.y;
    vec.x = f1 * pos.x - f2 * pos.y;
    vec.y = f2 * pos.x + f1 * pos.y;

    vec.x = (kp->center_org.x - vec.x) * kp->dpd2pos_scale;
    vec.y = (kp->center_org.y - vec.y) * kp->dpd2pos_scale;

    pos.x = -kp->accXY_nrm_hori.y * vec.x + kp->accXY_nrm_hori.x * vec.y;
    pos.y = -kp->accXY_nrm_hori.x * vec.x - kp->accXY_nrm_hori.y * vec.y;
    kp->_5D8 = pos;
    if (sp->dpd_valid_fg == 0) {
        sp->pos = pos;
        sp->vec = Vec2_0;
        sp->speed = 0.0f;
    } else {
        vec.x = pos.x - sp->pos.x;
        vec.y = pos.y - sp->pos.y;
        f1 = sqrt(vec.x * vec.x + vec.y * vec.y);

        if (kp->pos_play_mode == KPAD_PLAY_MODE_LOOSE) {
            if (f1 >= kp->pos_play_radius) {
                f2 = 1.0f;
            } else {
                f2 = f1 / kp->pos_play_radius;
                f2 *= f2;
                f2 *= f2;
            }
            f2 *= kp->pos_sensitivity;

            sp->vec.x = f2 * vec.x;
            sp->vec.y = f2 * vec.y;
            sp->speed = sqrt(sp->vec.x * sp->vec.x + sp->vec.y * sp->vec.y);

            sp->pos.x += sp->vec.x;
            sp->pos.y += sp->vec.y;
        } else {
            if (f1 > kp->pos_play_radius) {
                f1 = (f1 - kp->pos_play_radius) / f1 * kp->pos_sensitivity;
                sp->vec.x = f1 * vec.x;
                sp->vec.y = f1 * vec.y;
                sp->speed = sqrt(sp->vec.x * sp->vec.x + sp->vec.y * sp->vec.y);

                sp->pos.x += sp->vec.x;
                sp->pos.y += sp->vec.y;
            } else {
                sp->vec = Vec2_0;
                sp->speed = 0.0f;
            }
        }
    }

    sp->dpd_valid_fg = valid_fg_next;
}

static void calc_obj_horizon(KPADInsideStatus* kp) {
    f32 f1, f2, vx, vy;

    vx = kp->kobj_regular[1].center.x - kp->kobj_regular[0].center.x;
    vy = kp->kobj_regular[1].center.y - kp->kobj_regular[0].center.y;
    f1 = sqrt(vx * vx + vy * vy);
    kp->sec_length = f1;

    f2 = 1.0f / f1;
    kp->sec_dist = kp->dist_vv1 * f2;

    vx *= f2;
    vy *= f2;
    kp->sec_nrm.x = vx;
    kp->sec_nrm.y = vy;

    kp->obj_horizon.x = kp->sec_nrm_hori.x * vx + kp->sec_nrm_hori.y * vy;
    kp->obj_horizon.y = kp->sec_nrm_hori.y * vx - kp->sec_nrm_hori.x * vy;
}

static void get_kobj(KPADInsideStatus* kp, DPDObject* wobj_p) {
    const f32 dpd_scale = 2.0f / (f32)KPAD_DPD_RESO_WX;
    const f32 dpd_cx = (f32)(KPAD_DPD_RESO_WX - 1) / (f32)KPAD_DPD_RESO_WX;
    const f32 dpd_cy = (f32)(KPAD_DPD_RESO_WY - 1) / (f32)KPAD_DPD_RESO_WX;

    KPADObject* kobj_p;

    kobj_p = &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1];
    do {
        if (wobj_p->size) {
            kobj_p->center.x = (f32)(s32)wobj_p->x * dpd_scale - dpd_cx;
            kobj_p->center.y = (f32)(s32)wobj_p->y * dpd_scale - dpd_cy;

            kobj_p->error_fg = 0;
            kobj_p->state_fg = 0;
        } else {
            kobj_p->error_fg = -1;
        }

        --wobj_p;
    } while (--kobj_p >= kp->kobj_sample);
}

static void check_kobj_outside_frame(KPADInsideStatus* kp, KPADObject* kobj_t) {
    KPADObject* kobj_p = &kobj_t[WPAD_DPD_MAX_OBJECTS - 1];

    do {
        if (kobj_p->error_fg < 0) {
            continue;
        }

        if (kobj_p->center.x <= kp->kobj_frame_min.x || kobj_p->center.x >= kp->kobj_frame_max.x || kobj_p->center.y <= kp->kobj_frame_min.y ||
            kobj_p->center.y >= kp->kobj_frame_max.y) {
            kobj_p->error_fg |= 1;
        }
    } while (--kobj_p >= kobj_t);
}

static void check_kobj_same_position(KPADObject* kobj_t) {
    KPADObject *op1, *op2;

    op1 = kobj_t;
    do {
        if (op1->error_fg != 0) {
            continue;
        }

        op2 = op1 + 1;
        do {
            if (op2->error_fg != 0) {
                continue;
            }

            if (op1->center.x == op2->center.x && op1->center.y == op2->center.y) {
                op2->error_fg |= 2;
            }
        } while (++op2 <= &kobj_t[WPAD_DPD_MAX_OBJECTS - 1]);
    } while (++op1 < &kobj_t[WPAD_DPD_MAX_OBJECTS - 1]);
}

void read_kpad_dpd(KPADInsideStatus* kp, KPADUnifiedWpadStatus* uwp) {
    KPADStatus* sp = &kp->status;
    KPADObject* op1;
    s8 valid_fg_next;

    if (uwp->fmt == WPAD_FMT_CORE_ACC_DPD || uwp->fmt == WPAD_FMT_FREESTYLE_ACC_DPD || uwp->fmt == WPAD_FMT_CLASSIC_ACC_DPD ||
        (uwp->fmt == WPAD_FMT_GUITAR && kp->_643) || (uwp->fmt == WPAD_FMT_DRUM && kp->_643) || (uwp->fmt == WPAD_FMT_TAIKO && kp->_643) ||
        (uwp->fmt == WPAD_FMT_MOTION_PLUS && kp->_643)) {
        get_kobj(kp, &uwp->u.core.obj[WPAD_DPD_MAX_OBJECTS - 1]);
    } else {
        op1 = &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1];
        do {
            op1->error_fg = -1;
        } while (--op1 >= kp->kobj_sample);
    }

    check_kobj_outside_frame(kp, kp->kobj_sample);
    check_kobj_same_position(kp->kobj_sample);
    kp->valid_objs = 0;
    op1 = &kp->kobj_sample[WPAD_DPD_MAX_OBJECTS - 1];
    do {
        if (op1->error_fg == 0) {
            ++kp->valid_objs;
        }
    } while (--op1 >= kp->kobj_sample);

    if (sp->acc_vertical.x <= kp_err_up_inpr) {
        goto LABEL_select_NG;
    }

    if (sp->dpd_valid_fg == 2 || sp->dpd_valid_fg == -2) {
        if (kp->valid_objs >= 2) {
            valid_fg_next = select_2obj_continue(kp);
            if (valid_fg_next) {
                goto LABEL_select_OK;
            }
        }
        if (kp->valid_objs >= 1) {
            valid_fg_next = select_1obj_continue(kp);
            if (valid_fg_next) {
                goto LABEL_select_OK;
            }
        }
    } else if (sp->dpd_valid_fg == 1 || sp->dpd_valid_fg == -1) {
        if (kp->valid_objs >= 2) {
            valid_fg_next = select_2obj_first(kp);
            if (valid_fg_next) {
                goto LABEL_select_OK;
            }
        }
        if (kp->valid_objs >= 1) {
            valid_fg_next = select_1obj_continue(kp);
            if (valid_fg_next) {
                goto LABEL_select_OK;
            }
        }
    } else {
        if (kp->valid_objs >= 2) {
            valid_fg_next = select_2obj_first(kp);

            if (valid_fg_next) {
                goto LABEL_select_OK;
            }
        }
        if (kp->valid_objs == 1) {
            valid_fg_next = select_1obj_first(kp);
            if (valid_fg_next)
                goto LABEL_select_OK;
        }
    }

LABEL_select_NG:
    valid_fg_next = 0;

LABEL_select_OK:
    if (valid_fg_next) {
        calc_obj_horizon(kp);
        if (kp->ah_circle_ct == 0) {
            if (kp->obj_horizon.x * kp->acc_horizon.x + kp->obj_horizon.y * kp->acc_horizon.y <= kp_err_acc_inpr) {
                valid_fg_next = 0;

                kp->kobj_regular[0].error_fg = kp->kobj_regular[1].error_fg = 1;
            }
        }

        if (sp->dpd_valid_fg == 2 && valid_fg_next == 2) {
            if (kp->dpd_valid2_ct == 200) {
                kp->trust_sec_length = kp->sec_length;
            } else {
                ++kp->dpd_valid2_ct;
            }
        } else {
            kp->dpd_valid2_ct = 0;
        }
    } else {
        kp->dpd_valid2_ct = 0;
    }

    calc_dpd_variable(kp, valid_fg_next);
}

void clamp_stick_circle(Vec2* stick, s32 sx, s32 sy, s32 min, s32 max) {
    f32 length;
    f32 fx = (f32)sx;
    f32 fy = (f32)sy;
    f32 fmin = (f32)min;
    f32 fmax = (f32)max;

    length = sqrt(fx * fx + fy * fy);

    if (length <= fmin) {
        stick->x = stick->y = 0.0f;

    } else if (length >= fmax) {
        stick->x = fx / length;
        stick->y = fy / length;

    } else {
        length = (length - fmin) / (fmax - fmin) / length;
        stick->x = fx * length;
        stick->y = fy * length;
    }
}

void clamp_stick_cross(Vec2* stick, s32 sx, s32 sy, s32 min, s32 max) {
    f32 length;

    if (sx < 0) {
        clamp_trigger(&stick->x, -sx, min, max);
        stick->x = -stick->x;
    } else {
        clamp_trigger(&stick->x, sx, min, max);
    }
    if (sy < 0) {
        clamp_trigger(&stick->y, -sy, min, max);
        stick->y = -stick->y;
    } else {
        clamp_trigger(&stick->y, sy, min, max);
    }

    length = stick->x * stick->x + stick->y * stick->y;
    if (length > 1.0f) {
        length = sqrt(length);
        stick->x /= length;
        stick->y /= length;
    }
}

#define RESET_EX_FS()                                                                                                  \
    ep->fs.stick = Vec2_0;                                                                                             \
    ep->fs.acc.x = ep->fs.acc.z = 0.0f;                                                                                \
    ep->fs.acc.y = -1.0f;                                                                                              \
    ep->fs.acc_value = 1.0f;                                                                                           \
    ep->fs.acc_speed = 0.0f;

#define RESET_EX_CL()                                                                                                  \
    ep->cl.lstick = Vec2_0;                                                                                            \
    ep->cl.rstick = Vec2_0;                                                                                            \
    ep->cl.ltrigger = ep->cl.rtrigger = 0.0f;                                                                          \
    ep->cl.hold = ep->cl.trig = ep->cl.release = 0x00000000;                                                           \
    kp->btn_cl_repeat_time = 0;                                                                                        \
    kp->btn_cl_repeat_next = kp->btn_repeat_delay;

void read_kpad_ext(KPADInsideStatus* kp, KPADUnifiedWpadStatus* uwp) {
    KPADEXStatus* ep = &kp->status.ex_status;
    void (*clampStickFuncp)(Vec2* stick, s32 sx, s32 sy, s32 min, s32 max);
    f64 weight;
    s32 i;

    clampStickFuncp = kp_stick_clamp_cross ? clamp_stick_cross : clamp_stick_circle;

    if (uwp->u.core.dev == WPAD_DEV_FREESTYLE &&
        (uwp->fmt == WPAD_FMT_FREESTYLE || uwp->fmt == WPAD_FMT_FREESTYLE_ACC || uwp->fmt == WPAD_FMT_FREESTYLE_ACC_DPD)) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            RESET_EX_FS()
        }

        clampStickFuncp(&ep->fs.stick, uwp->u.fs.fsStickX, uwp->u.fs.fsStickY, kp_fs_fstick_min, kp_fs_fstick_max);
    } else if (uwp->u.core.dev == WPAD_DEV_CLASSIC &&
               (uwp->fmt == WPAD_FMT_CLASSIC || uwp->fmt == WPAD_FMT_CLASSIC_ACC || uwp->fmt == WPAD_FMT_CLASSIC_ACC_DPD)) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            RESET_EX_CL()
        }

        clampStickFuncp(&ep->cl.lstick, uwp->u.cl.clLStickX, uwp->u.cl.clLStickY, kp_cl_stick_min, kp_cl_stick_max);
        clampStickFuncp(&ep->cl.rstick, uwp->u.cl.clRStickX, uwp->u.cl.clRStickY, kp_cl_stick_min, kp_cl_stick_max);
        clamp_trigger(&ep->cl.ltrigger, uwp->u.cl.clTriggerL, kp_cl_trigger_min, kp_cl_trigger_max);
        clamp_trigger(&ep->cl.rtrigger, uwp->u.cl.clTriggerR, kp_cl_trigger_min, kp_cl_trigger_max);
    } else if ((uwp->u.core.dev == WPAD_DEV_GUITAR && uwp->fmt == WPAD_FMT_GUITAR) ||
               (uwp->u.core.dev == WPAD_DEV_DRUM && uwp->fmt == WPAD_FMT_DRUM)) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            RESET_EX_CL()
        }

        clampStickFuncp(&ep->cl.lstick, uwp->u.cl.clLStickX, uwp->u.cl.clLStickY, kp_cl_stick_min, kp_cl_stick_max);
        clamp_trigger(&ep->cl.rstick.x, uwp->u.cl.clRStickX, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.rstick.y, uwp->u.cl.clRStickY, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.ltrigger, uwp->u.cl.clTriggerL, kp_ex_trigger_min, kp_ex_trigger_max);
        clamp_trigger(&ep->cl.rtrigger, uwp->u.cl.clTriggerR, kp_ex_trigger_min, kp_ex_trigger_max);
    } else if (uwp->u.core.dev == WPAD_DEV_TRAIN && uwp->fmt == WPAD_FMT_TRAIN) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            RESET_EX_CL()
        }

        ep->cl.lstick.x = ep->cl.lstick.y = 0.0f;
        ep->cl.rstick.x = ep->cl.rstick.y = 0.0f;
        clamp_trigger(&ep->cl.ltrigger, uwp->u.tr.brake, kp_ex_trigger_min, kp_ex_trigger_max);
        clamp_trigger(&ep->cl.rtrigger, uwp->u.tr.mascon, kp_ex_trigger_min, kp_ex_trigger_max);
    } else if (uwp->u.core.dev == WPAD_DEV_TAIKO && uwp->fmt == WPAD_FMT_TAIKO) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            RESET_EX_CL()
        }

        clamp_trigger(&ep->cl.lstick.x, uwp->u.cl.clLStickX, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.lstick.y, uwp->u.cl.clLStickY, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.rstick.x, uwp->u.cl.clRStickX, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.rstick.y, uwp->u.cl.clRStickY, kp_ex_analog_min, kp_ex_analog_max);
        clamp_trigger(&ep->cl.ltrigger, uwp->u.cl.clTriggerL, kp_ex_trigger_min, kp_ex_trigger_max);
        clamp_trigger(&ep->cl.rtrigger, uwp->u.cl.clTriggerR, kp_ex_trigger_min, kp_ex_trigger_max);
    } else if (uwp->u.core.dev == WPAD_DEV_BALANCE_CHECKER && uwp->fmt == WPAD_FMT_BALANCE_CHECKER) {
        ep->bl.weight_err = WBCRead(&uwp->u.bl, ep->bl.weight, 4);
        if (WBCGetBatteryLevel(uwp->u.bl.battery) == 0) {
            ep->bl.weight_err = -1;
        } else if (kp_wbc_enabled < 0) {
            ep->bl.weight_err = -6;
        } else if (kp_wbc_zero_point_done == 0) {
            ep->bl.weight_err = -7;
        } else if (kp_wbc_zero_point_done <= 3) {
            if (ep->bl.weight_err == 1) {
                kp_wbc_zero_point_done = -1;
                kp_wbc_tgc_weight_done = 0;
            }
            if (kp_wbc_zero_point_done < 0) {
                ep->bl.weight_err = -4;
            } else {
                ep->bl.weight_err = -8;
            }
        } else if (ep->bl.weight_err == -2) {
            ep->bl.weight_err = -2;
        } else if (ep->bl.weight_err >= 0) {
            weight = ep->bl.weight[3] + (ep->bl.weight[2] + (ep->bl.weight[0] + ep->bl.weight[1]));
            for (i = 0; i < 4; i++) {
                kp_wbc_weight_ave[i] = (kp_wbc_ave_count * kp_wbc_weight_ave[i] + ep->bl.weight[i]) / (1.0f + kp_wbc_ave_count);
                ep->bl.weight_ave[i] = kp_wbc_weight_ave[i];
            }

            if (weight > 150.0) {
                ep->bl.weight_err = -5;
            } else if (kp_wbc_tgc_weight_done == 1 || kp_wbc_tgc_weight_done == 2) {
                kp_wbc_tgc_weight_err = 1;
                kp_wbc_tgc_weight_wait++;
                if (kp_wbc_tgc_weight_wait > 2000) {
                    kp_wbc_tgc_weight_err = (kp_wbc_tgc_weight_done == 1) ? -3 : -1;
                    kp_wbc_tgc_weight_done = 0;
                } else if (kp_wbc_tgc_weight_done == 1) {
                    if (weight >= 2.0) {
                        kp_wbc_tgc_weight_done = 2;
                        kp_wbc_ave_sample_count = 0;
                        kp_wbc_min_weight = kp_wbc_max_weight = weight;
                    }
                } else if (weight < 2.0) {
                    kp_wbc_tgc_weight_done = 1;
                } else {
                    kp_wbc_max_weight = weight - kp_wbc_min_weight;
                    if (kp_wbc_max_weight < 0.0) {
                        kp_wbc_max_weight *= -1.0;
                    }
                    if (kp_wbc_max_weight < 0.3) {
                        kp_wbc_ave_sample_count++;
                    } else {
                        kp_wbc_ave_sample_count = 0;
                        kp_wbc_min_weight += 0.5 * (weight - kp_wbc_min_weight);
                    }
                    if (kp_wbc_ave_sample_count > 100) {
                        kp_wbc_tgc_weight_done = 3;
                        kp_wbc_ave_sample_count = 0;
                        kp_wbc_min_weight = kp_wbc_max_weight = weight;
                    }
                }
            } else if (kp_wbc_tgc_weight_done == 3) {
                kp_wbc_tgc_weight_err = -4;
                kp_wbc_ave_sample_count++;
                for (i = 0; i < 4; i++) {
                    kp_wbc_ave_sample[i] =
                        ((f64)(kp_wbc_ave_sample_count - 1) * kp_wbc_ave_sample[i] + ep->bl.weight[i]) / (f64)kp_wbc_ave_sample_count;
                }
                if (kp_wbc_min_weight > weight) {
                    kp_wbc_min_weight = weight;
                }
                if (kp_wbc_max_weight < weight) {
                    kp_wbc_max_weight = weight;
                }
                if ((f32)kp_wbc_ave_sample_count == kp_wbc_ave_count) {
                    weight = kp_wbc_ave_sample[3] + (kp_wbc_ave_sample[2] + (kp_wbc_ave_sample[0] + kp_wbc_ave_sample[1]));
                    kp_wbc_tgc_weight_err = 0;
                    WBCGetTGCWeight(weight, &kp_wbc_tgc_weight, &uwp->u.bl);
                    if (weight - kp_wbc_min_weight > 0.3 || kp_wbc_max_weight - weight > 0.3) {
                        kp_wbc_tgc_weight_err = -1;
                    }
                    kp_wbc_tgc_weight_done = 0;
                }
            }
        }

        ep->bl.tgc_weight = kp_wbc_tgc_weight;
        ep->bl.tgc_weight_err = kp_wbc_tgc_weight_err;
    } else if (((uwp->u.core.dev >= WPAD_DEV_MOTION_PLUS && uwp->u.core.dev <= WPAD_DEV_MPLS_CLASSIC) ||
                uwp->u.core.dev == WPAD_DEV_MPLS_PT_FUTURE) &&
               uwp->fmt == WPAD_FMT_MOTION_PLUS) {
        if (kp->exResetReq) {
            kp->exResetReq = FALSE;
            if (uwp->u.core.dev == WPAD_DEV_MPLS_FREESTYLE && (uwp->u.mp.stat & 0x40)) {
                RESET_EX_FS()
            }
            if (uwp->u.core.dev == WPAD_DEV_MPLS_CLASSIC && (uwp->u.mp.stat & 0x40)) {
                RESET_EX_CL()
            }
        }

        if ((uwp->u.mp.stat & 0x01) && (uwp->u.mp.stat & 0x40)) {
            if (uwp->u.core.dev == WPAD_DEV_MPLS_FREESTYLE) {
                clampStickFuncp(&ep->fs.stick, uwp->u.mp.ext.fs.fsStickX, uwp->u.mp.ext.fs.fsStickY, kp_fs_fstick_min, kp_fs_fstick_max);
            } else if (uwp->u.core.dev == WPAD_DEV_MPLS_CLASSIC) {
                clampStickFuncp(&ep->cl.lstick, uwp->u.mp.ext.cl.clLStickX, uwp->u.mp.ext.cl.clLStickY, kp_cl_stick_min, kp_cl_stick_max);
                clampStickFuncp(&ep->cl.rstick, uwp->u.mp.ext.cl.clRStickX, uwp->u.mp.ext.cl.clRStickY, kp_cl_stick_min, kp_cl_stick_max);
                clamp_trigger(&ep->cl.ltrigger, uwp->u.mp.ext.cl.clTriggerL, kp_cl_trigger_min, kp_cl_trigger_max);
                clamp_trigger(&ep->cl.rtrigger, uwp->u.mp.ext.cl.clTriggerR, kp_cl_trigger_min, kp_cl_trigger_max);
            }
        }
    }
}

static void KPADiMplsSamplingCallback(s32 chan, KPADMPStatus* mpStatus) {
    KPADInsideStatus* kp = &inside_kpads[chan];

    if (kp->mplsStatus == NULL) {
        return;
    }

    --kp->mplsStatus;
    kp->mplsStatus->mpls = *mpStatus;
}

s32 KPADRead(s32 chan, KPADStatus samplingBufs[], u32 length) {
    return KPADiRead(chan, samplingBufs, length, NULL, FALSE);
}

#define KPAD_CORE_BUTTON_MASK 0x9f1f

#define LAST_BUTTONS(uwp, dev)                                                                                         \
    switch ((uwp)->u.core.err) {                                                                                       \
    case WPAD_ERR_NONE:                                                                                                \
        if ((dev) == WPAD_DEV_FREESTYLE) {                                                                             \
            lastFsButton = (uwp)->u.core.button;                                                                       \
            lastClButton = 0;                                                                                          \
        } else if ((dev) == WPAD_DEV_CLASSIC || ((dev) >= WPAD_DEV_TRAIN && (dev) <= WPAD_DEV_TAIKO)) {                \
            lastClButton = (uwp)->u.cl.clButton;                                                                       \
            lastFsButton = 0;                                                                                          \
        } else if ((dev) == WPAD_DEV_MPLS_FREESTYLE && ((uwp)->u.mp.stat & 0x40) && ((uwp)->u.mp.stat & 0x01)) {       \
            lastFsButton = (uwp)->u.core.button;                                                                       \
            lastClButton = 0;                                                                                          \
        } else if ((dev) == WPAD_DEV_MPLS_CLASSIC && ((uwp)->u.mp.stat & 0x40) && ((uwp)->u.mp.stat & 0x01)) {         \
            lastClButton = (uwp)->u.mp.ext.cl.clButton;                                                                \
            lastFsButton = 0;                                                                                          \
        } else {                                                                                                       \
            lastFsButton = lastClButton = 0;                                                                           \
        }                                                                                                              \
    case WPAD_ERR_CORRUPTED:                                                                                           \
    case WPAD_ERR_BUSY:                                                                                                \
        lastCoreButton = (uwp)->u.core.button & KPAD_CORE_BUTTON_MASK;                                                 \
        break;                                                                                                         \
                                                                                                                       \
    default:                                                                                                           \
        break;                                                                                                         \
    }

s32 KPADiRead(s32 chan, KPADStatus samplingBufs[], u32 length, s32* err, BOOL ex) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    KPADTmpStatus* tp;
    KPADUnifiedWpadStatus* uwp;
    KPADStatus save;
    KPADStatus raw;
    s32 result = 0;
    s32 idx;
    s32 return_ct = 0;
    s32 copy_ct;
    BOOL enabled;
    u32 lastCoreButton;
    u32 lastFsButton;
    u32 lastClButton;
    u32 lastDev;
    u32 tick;
    u32 samples;
    f64 time;
    f64 dt;

    if (!kp_initialized) {
        result = -5;
        goto finish;
    }

    if (WPADGetStatus() != WPAD_STATE_SETUP) {
        result = -3;
        goto finish;
    }

    enabled = OSDisableInterrupts();
    if (kp->readLocked) {
        OSRestoreInterrupts(enabled);
        result = -4;
        goto finish;
    }
    kp->readLocked = TRUE;

    if (WPADProbe(chan, NULL) == WPAD_ERR_NO_CONTROLLER) {
        reset_kpad(chan);
        if (kp->dpd_ctrl_callback && kp->dpdPreCallbackDone && !kp->dpdPostCallbackDone) {
            KPADiControlDpdCallback(chan, WPAD_ERR_NONE);
        }
        if (kp->mpls_ctrl_callback && kp->mplsPostCallbackDone && !kp->mplsPreCallbackDone) {
            KPADiControlMplsCallback(chan, WPAD_ERR_NONE);
        }
        kp->readLocked = FALSE;
        OSRestoreInterrupts(enabled);
        result = -2;
        goto finish;
    }

    OSRestoreInterrupts(enabled);

    if (kp->resetReq) {
        kp->status.wpad_err = WPAD_ERR_INVALID;
        reset_kpad(chan);
    }

    save = samplingBufs[0];

    if (kp->bufCount && samplingBufs && length) {
        enabled = OSDisableInterrupts();

        copy_ct = kp->bufCount;
        if ((u32)copy_ct > length) {
            copy_ct = length;
        }
        kp->bufCount = 0;

        tick = kp->tick[0];
        kp->tick[0] = kp->tick[1];
        kp->tick[1] = kp->tick[2];
        kp->tick[2] = kp->tick[3];
        time = (f64)(((s64)kp->tick[3] + 0x100000000LL - tick) & 0xFFFFFFFF) / (f64)OS_TIMER_CLOCK;
        if (time > 0.3) {
            time = 0.3;
        }

        samples = kp->readCount[0] + kp->readCount[1] + copy_ct;
        kp->readCount[0] = kp->readCount[1];
        kp->readCount[1] = copy_ct;
        dt = time / (f64)samples;

        return_ct = copy_ct;
        tp = (KPADTmpStatus*)samplingBufs + copy_ct;

        idx = (s32)(kp->bufIdx - copy_ct);
        if (idx < 0) {
            idx += kp->uniRingBufExLen + KPAD_RING_BUFS;
        }

        do {
            if (idx >= KPAD_RING_BUFS) {
                uwp = &kp->uniRingBufEx[idx - KPAD_RING_BUFS];
            } else {
                uwp = &kp->uniRingBuf[idx];
            }
            --tp;
            tp->w = *uwp;
            idx++;
            if (idx >= kp->uniRingBufExLen + KPAD_RING_BUFS) {
                idx = 0;
            }
        } while (--copy_ct > 0);

        OSRestoreInterrupts(enabled);

        copy_ct = return_ct;
        tp = (KPADTmpStatus*)samplingBufs + return_ct;

        if (kp->btnProcMode == 1) {
            do {
                --tp;
                uwp = &tp->w;
                if (kp->status.dev_type != uwp->u.core.dev) {
                    kp->status.dev_type = uwp->u.core.dev;
                    kp->exResetReq = TRUE;
                }
                kp->status.wpad_err = uwp->u.core.err;
                kp->status.data_format = uwp->fmt;

                lastCoreButton = lastFsButton = lastClButton = KPAD_BUTTON_MASK;
                lastDev = kp->status.dev_type;
                LAST_BUTTONS(uwp, lastDev)

                if (lastCoreButton == KPAD_BUTTON_MASK) {
                    lastCoreButton = kp->status.hold & KPAD_CORE_BUTTON_MASK;
                }
                if (lastFsButton == KPAD_BUTTON_MASK) {
                    lastFsButton = kp->status.hold;
                }
                if (lastClButton == KPAD_BUTTON_MASK) {
                    lastClButton = kp->status.ex_status.cl.hold;
                }
                read_kpad_button(kp, lastDev, 1, lastCoreButton, lastFsButton, lastClButton);

                switch (uwp->u.core.err) {
                case WPAD_ERR_NONE:
                    read_kpad_ext(kp, uwp);
                case WPAD_ERR_CORRUPTED:
                    read_kpad_acc(kp, uwp);
                    read_kpad_dpd(kp, uwp);
                    break;

                default:
                    if (!ex) {
                        kp->status.dpd_valid_fg = 0;
                    }
                    break;
                }
                tp->k = kp->status;
            } while (--copy_ct > 0);
        } else {
            lastCoreButton = lastFsButton = lastClButton = KPAD_BUTTON_MASK;
            do {
                --tp;
                uwp = &tp->w;
                if (kp->status.dev_type != uwp->u.core.dev) {
                    kp->status.dev_type = uwp->u.core.dev;
                    kp->exResetReq = TRUE;
                }
                lastDev = uwp->u.core.dev;
                LAST_BUTTONS(uwp, lastDev)
            } while (--copy_ct > 0);

            if (lastCoreButton == KPAD_BUTTON_MASK) {
                lastCoreButton = kp->status.hold & KPAD_CORE_BUTTON_MASK;
            }
            if (lastFsButton == KPAD_BUTTON_MASK) {
                lastFsButton = kp->status.hold;
            }
            if (lastClButton == KPAD_BUTTON_MASK) {
                lastClButton = kp->status.ex_status.cl.hold;
            }
            read_kpad_button(kp, lastDev, return_ct, lastCoreButton, lastFsButton, lastClButton);

            copy_ct = return_ct;
            tp = (KPADTmpStatus*)samplingBufs + return_ct;
            do {
                --tp;
                uwp = &tp->w;
                kp->status.wpad_err = uwp->u.core.err;
                kp->status.data_format = uwp->fmt;

                switch (uwp->u.core.err) {
                case WPAD_ERR_NONE:
                    read_kpad_ext(kp, uwp);
                case WPAD_ERR_CORRUPTED:
                    read_kpad_acc(kp, uwp);
                    read_kpad_dpd(kp, uwp);
                    break;

                default:
                    if (!ex) {
                        kp->status.dpd_valid_fg = 0;
                    }
                    break;
                }
                tp->k = kp->status;
            } while (--copy_ct > 0);
        }

        if (KMPLSIsInit()) {
            kp->mplsStatus = &((KPADTmpStatus*)samplingBufs + return_ct)->k;
            raw.acc = kp->hard_acc;
            raw.pos = kp->_5D8;
            raw.horizon = kp->obj_horizon;
            raw.dpd_valid_fg = kp->status.dpd_valid_fg;
            KMPLSSetKpadRingBuffer(chan, kp->uniRingBuf, kp->uniRingBufEx, kp->uniRingBufExLen);
            KMPLSSetSamplingCallback(KPADiMplsSamplingCallback);
            KMPLSRead(chan, &kp->status.mpls, idx, return_ct, &raw, dt);
            samplingBufs[0] = kp->status;
        }
    }

    kp->readLocked = FALSE;

finish:
    if (return_ct == 0) {
        if (result == 0) {
            if (ex) {
                samplingBufs[0] = save;
            }
            result = -1;
        } else if (result == -2) {
            if (ex) {
                samplingBufs->dev_type = WPAD_DEV_NOT_FOUND;
                samplingBufs->data_format = WPAD_FMT_CORE;
                samplingBufs->wpad_err = WPAD_ERR_NO_CONTROLLER;
            }
        }
    }

    if (err) {
        *err = result;
    }
    return return_ct;
}

void KPADInit(void) {
    KPADInitEx(NULL, 0);
}

void KPADInitEx(KPADUnifiedWpadStatus* uniRingBufs, u32 length) {
    s32 i;
    KPADInsideStatus* kp;
    u32 idx;
    BOOL enabled;

    if (kp_initialized) {
        return;
    }

    WPADInit();
    enabled = OSDisableInterrupts();
    memset(inside_kpads, 0, sizeof(inside_kpads));
    kp_err_dist_max = (f32)(1.0f + (f32)WPADGetDpdSensitivity());

    i = 0;
    do {
        kp = &inside_kpads[i];
        kp->appConnectCallback = WPADSetConnectCallback(i, KPADiConnectCallback);
        kp->appSamplingCallback = WPADSetSamplingCallback(i, KPADiSamplingCallback);
        kp->_643 = FALSE;
        kp->dpdEnabled = TRUE;
        kp->dpdCmd = 0;
        kp->dpdPreCallbackDone = FALSE;
        kp->dpdPostCallbackDone = TRUE;
        kp->mplsModeInit = 0;
        kp->mplsCmd = 0;
        kp->mplsIssued = FALSE;
        kp->mplsCheck = 3;
        kp->mplsCmdIssued = kp->mplsMode = WPADiGetMplsStatus(i);
        kp->mplsPostCallbackDone = FALSE;
        kp->mplsPreCallbackDone = TRUE;
        kp->status.dev_type = WPAD_DEV_NOT_FOUND;
        kp->status.data_format = WPAD_FMT_CORE;
        kp->dist_org = idist_org;
        kp->accXY_nrm_hori = iaccXY_nrm_hori;
        kp->sec_nrm_hori = isec_nrm_hori;
        kp->center_org = icenter_org;
        calc_dpd2pos_scale(kp);
        kp->pos_play_radius = kp->hori_play_radius = kp->dist_play_radius = kp->acc_play_radius = 0.0f;
        kp->pos_sensitivity = kp->hori_sensitivity = kp->dist_sensitivity = kp->acc_sensitivity = 1.0f;
        kp->pos_play_mode = kp->hori_play_mode = kp->dist_play_mode = kp->acc_play_mode = KPAD_PLAY_MODE_LOOSE;

        KPADSetBtnRepeat(i, 0.0f, 0.0f);
        kp->btnProcMode = 0;
        KPADEnableAimingMode(i);
        kp->accScaleReq = TRUE;
        kp->fsAccRevise = 0;

        if (length != 0 && uniRingBufs != NULL) {
            kp->uniRingBufExLen = length / WPAD_MAX_CONTROLLERS;
            kp->uniRingBufEx = &uniRingBufs[kp->uniRingBufExLen * i];
        } else {
            kp->uniRingBufExLen = 0;
            kp->uniRingBufEx = NULL;
        }

        for (idx = 0; idx < KPAD_RING_BUFS; idx++) {
            kp->uniRingBuf[idx].u.core.err = WPAD_ERR_NO_CONTROLLER;
        }
        for (idx = 0; idx < kp->uniRingBufExLen; idx++) {
            kp->uniRingBufEx[idx].u.core.err = WPAD_ERR_NO_CONTROLLER;
        }
    } while (++i < WPAD_MAX_CONTROLLERS);

    kp_wbc_issued = FALSE;
    kp_wbc_enabled = FALSE;
    kp_wbc_ave_sample_count = 0;
    for (idx = 0; idx < 4; idx++) {
        kp_wbc_ave_sample[idx] = 0.0;
    }
    kp_wbc_tgc_weight_err = -2;
    kp_wbc_tgc_weight_wait = 0;
    kp_wbc_tgc_weight_done = 1;
    kp_wbc_zero_point_done = 0;

    WPADSetCallbackByKPAD(TRUE);
    KPADReset();

    MTXRowCol(kp_fs_rot, 0, 0) = 1;
    MTXRowCol(kp_fs_rot, 0, 1) = 0;
    MTXRowCol(kp_fs_rot, 0, 2) = 0;
    MTXRowCol(kp_fs_rot, 0, 3) = 0;
    MTXRowCol(kp_fs_rot, 1, 0) = 0;
    MTXRowCol(kp_fs_rot, 1, 1) = (f32)cos(MTXDegToRad(kp_fs_revise_deg));
    MTXRowCol(kp_fs_rot, 1, 2) = (f32)-sin(MTXDegToRad(kp_fs_revise_deg));
    MTXRowCol(kp_fs_rot, 1, 3) = 0;
    MTXRowCol(kp_fs_rot, 2, 0) = 0;
    MTXRowCol(kp_fs_rot, 2, 1) = (f32)sin(MTXDegToRad(kp_fs_revise_deg));
    MTXRowCol(kp_fs_rot, 2, 2) = (f32)cos(MTXDegToRad(kp_fs_revise_deg));
    MTXRowCol(kp_fs_rot, 2, 3) = 0;

    kp_initialized = TRUE;
    OSRestoreInterrupts(enabled);
    OSRegisterVersion(__KPADVersion);
}

void KPADShutdown(void) {
    KPADInsideStatus* kp;
    s32 chan;

    WPADSetCallbackByKPAD(FALSE);

    chan = 0;
    kp = inside_kpads;
    do {
        if (kp->appSamplingCallback) {
            WPADSetSamplingCallback(chan, kp->appSamplingCallback);
        } else {
            WPADSetSamplingCallback(chan, NULL);
        }
        if (kp->appConnectCallback) {
            WPADSetConnectCallback(chan, kp->appConnectCallback);
        } else {
            WPADSetConnectCallback(chan, NULL);
        }
        ++kp;
    } while (++chan < WPAD_MAX_CONTROLLERS);

    KMPLSShutdown();
    kp_initialized = FALSE;
}

static void set_obj_interval(f32 interval) {
    BOOL enabled = OSDisableInterrupts();
    kp_obj_interval = interval;
    kp_err_dist_min = interval / 0.383864f;
    kp_dist_vv1 = interval / 0.383864f;
    OSRestoreInterrupts(enabled);
}

void KPADReset(void) {
    s32 chan;
    set_obj_interval(kp_obj_interval);

    chan = WPAD_MAX_CONTROLLERS - 1;
    do {
        if (WPADGetStatus() == WPAD_STATE_SETUP) {
            WPADStopMotor(chan);
        }
        inside_kpads[chan].resetReq = TRUE;
    } while (--chan >= 0);
}

static void KPADiConnectCallback(s32 chan, s32 result) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    u32 idx;

    if (result == WPAD_ERR_NONE) {
        kp->lastDev = WPAD_DEV_CORE;
        kp->accScaleReq = TRUE;

        WPADSetCallbackByKPAD(FALSE);
        WPADSetSamplingCallback(chan, KPADiSamplingCallback);
        WPADSetCallbackByKPAD(TRUE);

        kp->_643 = FALSE;
        kp->dpdCmd = 0;
        kp->dpdIssued = FALSE;

        if (chan == WPAD_CHAN3) {
            kp_wbc_issued = FALSE;
            kp_wbc_enabled = FALSE;
            if (kp_wbc_zero_point_done != 4) {
                kp_wbc_zero_point_done = 0;
            }
            kp_wbc_tgc_weight_done = 0;
            kp_wbc_tgc_weight_err = -2;
        }

        kp->mplsIssued = FALSE;
        kp->mplsCheck = TRUE;
        kp->mplsMode = kp->mplsModeInit;
        kp->mplsCmdIssued = 0;
        kp->mplsPostCallbackDone = FALSE;
        kp->mplsPreCallbackDone = TRUE;
    } else {
        for (idx = 0; idx < KPAD_RING_BUFS; idx++) {
            kp->uniRingBuf[idx].u.core.err = WPAD_ERR_NO_CONTROLLER;
        }
        for (idx = 0; idx < kp->uniRingBufExLen; idx++) {
            kp->uniRingBufEx[idx].u.core.err = WPAD_ERR_NO_CONTROLLER;
        }

        KPADiControlDpdCallback(chan, WPAD_ERR_NONE);

        if (!kp->mplsPreCallbackDone && kp->mpls_ctrl_callback) {
            kp->mpls_ctrl_callback(chan, 1);
        }
    }

    if (kp->appConnectCallback) {
        kp->appConnectCallback(chan, result);
    }
}

WPADConnectCallback KPADSetConnectCallback(s32 chan, WPADConnectCallback callback) {
    BOOL enabled;
    WPADConnectCallback old;

    enabled = OSDisableInterrupts();
    old = inside_kpads[chan].appConnectCallback;
    inside_kpads[chan].appConnectCallback = callback;
    OSRestoreInterrupts(enabled);

    return old;
}

static void KPADiControlWbcCallback(s32 chan, s32 result) {
    kp_wbc_enabled = (result == WPAD_ERR_NONE);
    kp_wbc_failure_count = 0;
    kp_wbc_issued = FALSE;
}

static void KPADiUpdateTempWbcCallback(s32 chan, s32 result) {
    if (result == WPAD_ERR_NONE) {
        kp_wbc_zero_point_done = 2;
        kp_wbc_zero_point_wait = 100;
        kp_wbc_ave_sample_count = 0;
    }
    kp_wbc_issued = FALSE;
}

void KPADDisableDPD(s32 chan) {
    inside_kpads[chan].dpdEnabled = FALSE;
}

void KPADEnableDPD(s32 chan) {
    inside_kpads[chan].dpdEnabled = TRUE;
}

static void KPADiControlDpdCallback(s32 chan, s32 result) {
    KPADInsideStatus* kp = &inside_kpads[chan];

    if (result == WPAD_ERR_NONE) {
        if (kp->dpd_ctrl_callback && !kp->dpdPostCallbackDone) {
            kp->dpdPostCallbackDone = TRUE;
            kp->dpd_ctrl_callback(chan, 1);
            kp->dpdPreCallbackDone = FALSE;
        }
    }
    kp->_643 = (u8)WPADIsDpdEnabled(chan);
    kp->dpdIssued = FALSE;
}

static void KPADiControlMplsCallback(s32 chan, s32 result) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    s32 reason;

    kp->mplsIssued = FALSE;
    kp->mplsCheck = TRUE;

    if (result == WPAD_ERR_NONE) {
        kp->mplsCmdIssued = kp->mplsCmd;
        return;
    }

    if (result == WPAD_ERR_INVALID || result == WPAD_ERR_TRANSFER) {
        if (!kp->mplsPreCallbackDone && kp->mplsCmd != 0 && kp->mplsCmd == kp->mplsMode) {
            switch (kp->mplsCmd) {
            case 5:
                reason = -2;
                break;
            case 7:
                reason = -3;
                break;
            default:
                reason = -1;
                break;
            }
            kp->mplsPreCallbackDone = FALSE;
            if (kp->mpls_ctrl_callback) {
                kp->mpls_ctrl_callback(chan, reason);
            }
            kp->mplsPostCallbackDone = TRUE;
        }
    }
    kp->mplsCmdIssued = 0;
}

// TODO: the link dropped this function, so only its name and size (0xA0 bytes) are known; the body is a guess.
// Something compiled between KPADInitEx and KPADiSamplingCallback puts 0.005f and 0.01f into .sdata2, in this
// order and ahead of the sampling callback's own constants, followed by two more floats that the link dropped.
void KPADGetMplsZeroDriftMode(s32 chan, s32* mode) {
    f32 radius;
    s32 count;
    f32 power;

    KMPLSGetZeroDriftParam(chan, &radius, &count, &power);
    if (radius == 0.005f) {
        *mode = 2;
    } else if (radius == 0.01f) {
        *mode = 1;
    } else {
        *mode = 0;
    }
}

static void KPADiSamplingCallback(s32 chan) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    KPADUnifiedWpadStatus* uwp;
    u32 idx;
    u32 type;
    u32 curDpd;
    f32 aimClbr;
    s32 i;
    s32 reason;
    u8 mplsStatus;
    WPADAcc acc1G = {1, 1, 1};
    static struct {
        u8 dpd;
        u8 fmt;
    } table[] = {
        {0, WPAD_FMT_CORE_ACC},        {3, WPAD_FMT_CORE_ACC_DPD},      {0, WPAD_FMT_FREESTYLE_ACC}, {1, WPAD_FMT_FREESTYLE_ACC_DPD},
        {0, WPAD_FMT_CLASSIC_ACC},     {1, WPAD_FMT_CLASSIC_ACC_DPD},   {0, WPAD_FMT_GUITAR},        {1, WPAD_FMT_GUITAR},
        {0, WPAD_FMT_DRUM},            {1, WPAD_FMT_DRUM},              {0, WPAD_FMT_BALANCE_CHECKER}, {0, WPAD_FMT_BALANCE_CHECKER},
        {0, WPAD_FMT_TRAIN},           {0, WPAD_FMT_TRAIN},             {0, WPAD_FMT_TAIKO},         {1, WPAD_FMT_TAIKO},
        {0, WPAD_FMT_MOTION_PLUS},     {1, WPAD_FMT_MOTION_PLUS},       {0, WPAD_FMT_BULK},          {0, WPAD_FMT_BULK},
    };

    if (WPADProbe(chan, &type) == WPAD_ERR_NO_CONTROLLER) {
        goto finish;
    }

    idx = kp->bufIdx;
    if (idx >= kp->uniRingBufExLen + KPAD_RING_BUFS) {
        idx = 0;
    }

    if (idx >= KPAD_RING_BUFS) {
        uwp = &kp->uniRingBufEx[idx - KPAD_RING_BUFS];
    } else {
        uwp = &kp->uniRingBuf[idx];
    }
    WPADRead(chan, &uwp->u.core);
    uwp->fmt = (u8)WPADGetDataFormat(chan);

    kp->bufIdx = (u8)(idx + 1);
    if (kp->bufCount < kp->uniRingBufExLen + KPAD_RING_BUFS) {
        kp->bufCount++;
    }

    kp->tick[3] = kp->tick[4];
    kp->tick[4] = OSGetTick();

    if (type != kp->lastDev && type == WPAD_DEV_FREESTYLE) {
        kp->accScaleReq = TRUE;
    }

    if (kp->accScaleReq) {
        WPADGetAccGravityUnit(chan, WPAD_DEV_CORE, &acc1G);
        if (acc1G.x * acc1G.y * acc1G.z != 0) {
            kp->acc_scale_x = 1.0f / acc1G.x;
            kp->acc_scale_y = 1.0f / acc1G.y;
            kp->acc_scale_z = 1.0f / acc1G.z;
            kp->accScaleReq = FALSE;
        } else {
            kp->acc_scale_x = 1.0f / 100;
            kp->acc_scale_y = 1.0f / 100;
            kp->acc_scale_z = 1.0f / 100;
        }

        WPADGetAccGravityUnit(chan, WPAD_DEV_FREESTYLE, &acc1G);
        if (acc1G.x * acc1G.y * acc1G.z != 0) {
            kp->fs_acc_scale_x = 1.0f / acc1G.x;
            kp->fs_acc_scale_y = 1.0f / acc1G.y;
            kp->fs_acc_scale_z = 1.0f / acc1G.z;
        } else {
            kp->fs_acc_scale_x = 1.0f / 200;
            kp->fs_acc_scale_y = 1.0f / 200;
            kp->fs_acc_scale_z = 1.0f / 200;
        }
    }

    if (kp->aimReq) {
        if (kp->aimEnabled) {
            if (WPAD_SENSOR_BAR_POS_TOP == WPADGetSensorBarPosition()) {
                aimClbr = 0.2f;
            } else {
                aimClbr = -0.2f;
            }
        } else {
            aimClbr = 0.0f;
        }
        KPADSetSensorHeight(chan, aimClbr);

        kp->aimReq = FALSE;
    }

    switch (type) {
    case WPAD_DEV_CORE:
    case WPAD_DEV_FUTURE:
    case WPAD_DEV_NOT_SUPPORTED:
    case WPAD_DEV_UNKNOWN:
        idx = 0;
        break;

    case WPAD_DEV_FREESTYLE:
        idx = 2;
        break;

    case WPAD_DEV_CLASSIC:
        idx = 4;
        break;

    case WPAD_DEV_GUITAR:
        idx = 6;
        break;

    case WPAD_DEV_DRUM:
        idx = 8;
        break;

    case WPAD_DEV_BALANCE_CHECKER:
        idx = 10;
        break;

    case WPAD_DEV_TRAIN:
        idx = 12;
        break;

    case WPAD_DEV_TAIKO:
        idx = 14;
        break;

    case WPAD_DEV_MOTION_PLUS:
    case WPAD_DEV_MPLS_FREESTYLE:
    case WPAD_DEV_MPLS_CLASSIC:
    case WPAD_DEV_MPLS_PT_FUTURE:
        idx = 16;
        break;

    case WPAD_DEV_BULK_1:
    case WPAD_DEV_BULK_2:
    case WPAD_DEV_BULK_3:
    case WPAD_DEV_BULK_4:
    case WPAD_DEV_BULK_5:
    case WPAD_DEV_BULK_6:
    case WPAD_DEV_BULK_7:
    case WPAD_DEV_BULK_8:
        idx = 18;
        break;

    default:
        goto finish;
    }

    if (kp->dpdEnabled) {
        idx += 1;
    }

    curDpd = (u32)(WPADIsDpdEnabled(chan) ? kp->dpdCmd : 0);

    if (curDpd != table[idx].dpd) {
        if (kp->dpd_ctrl_callback && !kp->dpdPreCallbackDone) {
            kp->dpdPreCallbackDone = TRUE;
            kp->dpd_ctrl_callback(chan, 0);
            kp->dpdPostCallbackDone = FALSE;
        }
        if (!kp->dpdIssued) {
            kp->dpdIssued = TRUE;
            if (WPADControlDpd(chan, table[idx].dpd, KPADiControlDpdCallback) == WPAD_ERR_NONE) {
                kp->dpdCmd = table[idx].dpd;
            }
        }
    } else {
        if (uwp->fmt != table[idx].fmt) {
            WPADSetDataFormat(chan, table[idx].fmt);
        }
    }

    if (type == WPAD_DEV_BALANCE_CHECKER && !kp_wbc_issued) {
        if (kp_wbc_enabled > 2) {
            if (kp_wbc_zero_point_done == 1) {
                if (WPADControlBLC(chan, 0x00, KPADiUpdateTempWbcCallback) == WPAD_ERR_NONE) {
                    kp_wbc_issued = TRUE;
                }
            } else if (kp_wbc_zero_point_done == 2) {
                if (kp_wbc_zero_point_wait == 0) {
                    if (uwp->u.bl.temp == 127 || uwp->u.bl.temp == -128) {
                        kp_wbc_zero_point_done = 1;
                    } else {
                        kp_wbc_zero_point_done = 3;
                        kp_wbc_ave_sample_count = 0;
                    }
                } else {
                    kp_wbc_zero_point_wait--;
                }
            } else if (kp_wbc_zero_point_done == 3) {
                if (uwp->u.core.err == WPAD_ERR_NONE) {
                    kp_wbc_ave_sample_count++;
                    for (i = 0; i < 4; i++) {
                        kp_wbc_ave_sample[i] =
                            ((f64)(kp_wbc_ave_sample_count - 1) * kp_wbc_ave_sample[i] + (f64)uwp->u.bl.press[i]) / (f64)kp_wbc_ave_sample_count;
                    }
                    if ((f32)kp_wbc_ave_sample_count == kp_wbc_ave_count) {
                        kp_wbc_zero_point_done = 4;
                        kp_wbc_ave_sample_count = 0;
                        WBCRead(&uwp->u.bl, kp_wbc_weight_ave, 4);
                        WBCSetZEROPoint(kp_wbc_ave_sample, 4);
                    }
                }
            }
        } else if (kp_wbc_enabled == 0) {
            if (WPADControlBLC(chan, 0xAA, KPADiControlWbcCallback) == WPAD_ERR_NONE) {
                kp_wbc_issued = TRUE;
            }
        } else if (kp_wbc_enabled == 1) {
            if (kp_wbc_failure_count < 3) {
                if (WBCSetupCalibration() == 1) {
                    kp_wbc_enabled = 2;
                    kp_wbc_zero_point_wait = 0;
                } else {
                    kp_wbc_failure_count++;
                }
            } else {
                kp_wbc_enabled = -1;
            }
        } else if (kp_wbc_enabled == 2) {
            if (WBCGetCalibrationStatus()) {
                kp_wbc_enabled = 3;
                kp_wbc_failure_count = 0;
            } else {
                kp_wbc_zero_point_wait++;
                if (kp_wbc_zero_point_wait > kp_wbc_calib_count) {
                    kp_wbc_enabled = 1;
                    kp_wbc_failure_count++;
                }
            }
        }
    }

    mplsStatus = WPADiGetMplsStatus(chan);
    if (kp->mplsIssued) {
        goto finish;
    }

    if (kp->mplsPostCallbackDone && mplsStatus == kp->mplsCmdIssued && mplsStatus == kp->mplsMode) {
        if (kp->mplsMode == kp->mplsModeInit) {
            kp->mplsPostCallbackDone = FALSE;
            if (kp->mpls_ctrl_callback) {
                kp->mpls_ctrl_callback(chan, 1);
            }
            kp->mplsPreCallbackDone = TRUE;
        } else {
            kp->mplsMode = kp->mplsModeInit;
        }
    } else if (kp->mplsCheck) {
        kp->mplsCheck--;
        goto finish;
    } else {
        kp->mplsCmd = kp->mplsMode;
        if (mplsStatus != 0 && mplsStatus != kp->mplsCmd) {
            kp->mplsCmd = 0;
        }

        if (mplsStatus != kp->mplsCmd) {
            if (!kp->mplsPostCallbackDone) {
                kp->mplsCmdIssued = 0;
            }
            kp->mplsIssued = TRUE;
            if (!kp->mplsPostCallbackDone) {
                kp->mplsPostCallbackDone = TRUE;
                if (kp->mpls_ctrl_callback) {
                    if (mplsStatus != 0 || kp->mplsMode == 0 ||
                        !((kp->lastDev >= WPAD_DEV_MOTION_PLUS && kp->lastDev <= WPAD_DEV_MPLS_CLASSIC) || kp->lastDev == WPAD_DEV_MPLS_PT_FUTURE)) {
                        reason = 0;
                    } else if (kp->mplsMode == 5) {
                        reason = -2;
                    } else {
                        reason = -1;
                        if (kp->mplsMode == 7) {
                            reason = -3;
                        }
                    }
                    kp->mpls_ctrl_callback(chan, reason);
                    if (reason < 0 && kp->mplsModeInit == 0) {
                        kp->mplsMode = kp->mplsModeInit;
                        kp->mplsCmd = kp->mplsModeInit;
                    }
                }
                kp->mplsPreCallbackDone = FALSE;
            }
            WPADiControlMpls(chan, kp->mplsCmd, KPADiControlMplsCallback);
        } else {
            kp->mplsMode = kp->mplsModeInit;
        }
    }

    if (mplsStatus == 0 && kp->mplsModeInit == 0) {
        kp->mplsMode = kp->mplsModeInit;
    }

finish:
    kp->lastDev = type;
    if (kp->appSamplingCallback) {
        kp->appSamplingCallback(chan);
    }
}

WPADSamplingCallback KPADSetSamplingCallback(s32 chan, WPADSamplingCallback callback) {
    BOOL enabled;
    WPADSamplingCallback old;

    enabled = OSDisableInterrupts();
    old = inside_kpads[chan].appSamplingCallback;
    inside_kpads[chan].appSamplingCallback = callback;
    OSRestoreInterrupts(enabled);

    return old;
}

void KPADGetUnifiedWpadStatus(s32 chan, KPADUnifiedWpadStatus* dst, u32 count) {
    KPADInsideStatus* kp = &inside_kpads[chan];
    KPADUnifiedWpadStatus* uwp;
    BOOL enabled;
    u32 idx;

    if (count > kp->uniRingBufExLen + KPAD_RING_BUFS) {
        count = kp->uniRingBufExLen + KPAD_RING_BUFS;
    }

    enabled = OSDisableInterrupts();
    idx = kp->bufIdx;

    while (count-- != 0) {
        if (idx == 0) {
            idx = kp->uniRingBufExLen + KPAD_RING_BUFS - 1;
        } else {
            --idx;
        }

        if (idx >= KPAD_RING_BUFS) {
            uwp = &kp->uniRingBufEx[idx - KPAD_RING_BUFS];
        } else {
            uwp = &kp->uniRingBuf[idx];
        }

        if (WPADGetStatus() != WPAD_STATE_SETUP) {
            uwp->u.core.err = WPAD_ERR_INVALID;
        }
        memcpy(dst, uwp, sizeof(KPADUnifiedWpadStatus));
        ++dst;
    }

    OSRestoreInterrupts(enabled);
}
