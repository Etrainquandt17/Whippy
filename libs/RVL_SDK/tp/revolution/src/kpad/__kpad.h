#ifndef _REVOLUTION_KPAD_PRIVATE_H_
#define _REVOLUTION_KPAD_PRIVATE_H_

// KPAD as it is in the SDK of December 2009. The public <revolution/kpad.h> of
// this tree describes the library of 2006 and is shared with the HOME Menu
// library, so the types of this version are here and that header is not used.

#include <tp/revolution/include/revolution/mtx.h>
#include <tp/revolution/include/revolution/wpad.h>
#include "tp/revolution/include/revolution/types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Names the SDK's own KPAD source uses, where this tree's wpad.h has others.
#define WPAD_ERR_NONE WPAD_ERR_OK
#define WPAD_DEV_FREESTYLE WPAD_DEV_FS
#define WPAD_DEV_MPLS_FREESTYLE WPAD_DEV_MPLS_PT_FS
#define WPAD_DEV_MPLS_CLASSIC WPAD_DEV_MPLS_PT_CLASSIC
#define WPAD_DEV_NOT_FOUND WPAD_DEV_NONE
#define WPAD_DEV_UNKNOWN WPAD_DEV_INITIALIZING
#define WPAD_FMT_CORE WPAD_FMT_CORE_BTN
#define WPAD_FMT_CORE_ACC WPAD_FMT_CORE_BTN_ACC
#define WPAD_FMT_CORE_ACC_DPD WPAD_FMT_CORE_BTN_ACC_DPD
#define WPAD_FMT_FREESTYLE WPAD_FMT_FS_BTN
#define WPAD_FMT_FREESTYLE_ACC WPAD_FMT_FS_BTN_ACC
#define WPAD_FMT_FREESTYLE_ACC_DPD WPAD_FMT_FS_BTN_ACC_DPD
#define WPAD_FMT_CLASSIC WPAD_FMT_CLASSIC_BTN
#define WPAD_FMT_CLASSIC_ACC WPAD_FMT_CLASSIC_BTN_ACC
#define WPAD_FMT_CLASSIC_ACC_DPD WPAD_FMT_CLASSIC_BTN_ACC_DPD

#define KPAD_BUTTON_MASK 0x0000ffff
#define KPAD_BUTTON_RPT 0x80000000

#define KPAD_BTN_RPT_TIME_MAX 20000
#define KPAD_BTN_NO_RPT_DELAY 40000

#define KPAD_DPD_RESO_WX WPAD_DPD_IMG_RESO_WX
#define KPAD_DPD_RESO_WY WPAD_DPD_IMG_RESO_WY

#define KPAD_USE_OBJECTS 2

#define KPAD_RING_BUFS 16

typedef struct Vec2 {
    f32 x, y;
} Vec2;

typedef enum KPADPlayMode { KPAD_PLAY_MODE_LOOSE = 0, KPAD_PLAY_MODE_TIGHT } KPADPlayMode;

typedef union KPADEXStatus {
    struct {
        Vec2 stick;
        Vec acc;
        f32 acc_value;
        f32 acc_speed;
    } fs;

    struct {
        u32 hold;
        u32 trig;
        u32 release;
        Vec2 lstick;
        Vec2 rstick;
        f32 ltrigger;
        f32 rtrigger;
    } cl;

    struct {
        f64 tgc_weight;
        f64 weight[4];
        f64 weight_ave[4];
        s32 weight_err;
        s32 tgc_weight_err;
    } bl;
} KPADEXStatus;

typedef struct KPADMPDir {
    Vec X;
    Vec Y;
    Vec Z;
} KPADMPDir;

typedef struct KPADMPStatus {
    /* 0x00 */ Vec mpls;
    /* 0x0C */ Vec angle;
    /* 0x18 */ KPADMPDir dir;
} KPADMPStatus;

typedef struct KPADStatus {
    /* 0x00 */ u32 hold;
    /* 0x04 */ u32 trig;
    /* 0x08 */ u32 release;
    /* 0x0C */ Vec acc;
    /* 0x18 */ f32 acc_value;
    /* 0x1C */ f32 acc_speed;
    /* 0x20 */ Vec2 pos;
    /* 0x28 */ Vec2 vec;
    /* 0x30 */ f32 speed;
    /* 0x34 */ Vec2 horizon;
    /* 0x3C */ Vec2 hori_vec;
    /* 0x44 */ f32 hori_speed;
    /* 0x48 */ f32 dist;
    /* 0x4C */ f32 dist_vec;
    /* 0x50 */ f32 dist_speed;
    /* 0x54 */ Vec2 acc_vertical;
    /* 0x5C */ u8 dev_type;
    /* 0x5D */ s8 wpad_err;
    /* 0x5E */ s8 dpd_valid_fg;
    /* 0x5F */ u8 data_format;
    /* 0x60 */ KPADEXStatus ex_status;
    /* 0xB0 */ KPADMPStatus mpls;
    /* 0xEC */ u8 __padding[4];
} KPADStatus;

typedef struct KPADUnifiedWpadStatus {
    union {
        WPADStatus core;
        WPADFSStatus fs;
        WPADCLStatus cl;
        WPADTRStatus tr;
        WPADBLStatus bl;
        WPADMPStatus mp;
        WPADBKStatus bk;
    } u;
    /* 0x40 */ u8 fmt;
    /* 0x41 */ u8 padding;
} KPADUnifiedWpadStatus;

typedef struct {
    Vec2 center;
    s8 error_fg;
    s8 state_fg;
    s8 _fg_1;
    s8 _fg_2;
} KPADObject;

typedef union {
    KPADStatus k;
    KPADUnifiedWpadStatus w;
} KPADTmpStatus;

typedef void (*KPADControlDpdCallback)(s32 chan, s32 reason);
typedef void (*KPADMplsSamplingCallback)(s32 chan, KPADMPStatus* mpStatus);
typedef void (*KPADControlMplsCallback)(s32 chan, s32 reason);

typedef struct {
    /* 0x000 */ KPADStatus status;

    /* 0x0F0 */ f32 pos_play_radius;
    /* 0x0F4 */ f32 pos_sensitivity;
    /* 0x0F8 */ f32 hori_play_radius;
    /* 0x0FC */ f32 hori_sensitivity;
    /* 0x100 */ f32 dist_play_radius;
    /* 0x104 */ f32 dist_sensitivity;
    /* 0x108 */ f32 acc_play_radius;
    /* 0x10C */ f32 acc_sensitivity;

    /* 0x110 */ f32 dist_org;
    /* 0x114 */ Vec2 accXY_nrm_hori;
    /* 0x11C */ Vec2 sec_nrm_hori;
    /* 0x124 */ Vec2 center_org;
    /* 0x12C */ f32 dpd2pos_scale;

    /* 0x130 */ KPADObject kobj_sample[WPAD_DPD_MAX_OBJECTS];
    /* 0x160 */ KPADObject kobj_regular[KPAD_USE_OBJECTS];

    /* 0x178 */ s16 valid_objs;
    /* 0x17A */ u8 bufIdx;
    /* 0x17B */ u8 bufCount;
    /* 0x17C */ KPADStatus* mplsStatus;
    /* 0x180 */ KPADUnifiedWpadStatus uniRingBuf[KPAD_RING_BUFS];
    /* 0x5A0 */ KPADUnifiedWpadStatus* uniRingBufEx;
    /* 0x5A4 */ u32 uniRingBufExLen;

    /* 0x5A8 */ f32 sec_length;
    /* 0x5AC */ Vec2 sec_nrm;
    /* 0x5B4 */ f32 sec_dist;
    /* 0x5B8 */ f32 trust_sec_length;

    /* 0x5BC */ Vec hard_acc;
    /* 0x5C8 */ Vec2 obj_horizon;
    /* 0x5D0 */ Vec2 acc_horizon;
    /* 0x5D8 */ Vec2 _5D8;
    /* 0x5E0 */ Vec2 ah_circle_pos;
    /* 0x5E8 */ u16 ah_circle_ct;
    /* 0x5EA */ u8 dpd_valid2_ct;
    /* 0x5EB */ u8 readLocked;

    /* 0x5EC */ u16 btn_repeat_time;
    /* 0x5EE */ u16 btn_repeat_next;
    /* 0x5F0 */ u16 btn_repeat_delay;
    /* 0x5F2 */ u16 btn_repeat_pulse;
    /* 0x5F4 */ u16 btn_cl_repeat_time;
    /* 0x5F6 */ u16 btn_cl_repeat_next;

    /* 0x5F8 */ KPADControlDpdCallback dpd_ctrl_callback;

    /* 0x5FC */ f32 acc_scale_x;
    /* 0x600 */ f32 acc_scale_y;
    /* 0x604 */ f32 acc_scale_z;
    /* 0x608 */ f32 fs_acc_scale_x;
    /* 0x60C */ f32 fs_acc_scale_y;
    /* 0x610 */ f32 fs_acc_scale_z;

    /* 0x614 */ Vec2 kobj_frame_min;
    /* 0x61C */ Vec2 kobj_frame_max;
    /* 0x624 */ f32 err_dist_speed_1;
    /* 0x628 */ f32 err_dist_speedM_1;
    /* 0x62C */ f32 ah_circle_radius2;
    /* 0x630 */ f32 dist_vv1;
    /* 0x634 */ f32 err_dist_min;

    /* 0x638 */ WPADSamplingCallback appSamplingCallback;
    /* 0x63C */ WPADConnectCallback appConnectCallback;

    /* 0x640 */ u8 resetReq;
    /* 0x641 */ u8 exResetReq;
    /* 0x642 */ u8 dpdEnabled;
    /* 0x643 */ u8 _643; // whether the DPD is on, as WPADIsDpdEnabled last said
    /* 0x644 */ u8 dpdIssued;
    /* 0x645 */ u8 dpdCmd;
    /* 0x646 */ u8 dpdPreCallbackDone;
    /* 0x647 */ u8 dpdPostCallbackDone;
    /* 0x648 */ u8 aimReq;
    /* 0x649 */ u8 aimEnabled;
    /* 0x64A */ u8 fsAccRevise;
    /* 0x64B */ u8 btnProcMode;

    /* 0x64C */ KPADPlayMode pos_play_mode;
    /* 0x650 */ KPADPlayMode hori_play_mode;
    /* 0x654 */ KPADPlayMode dist_play_mode;
    /* 0x658 */ KPADPlayMode acc_play_mode;

    /* 0x65C */ u32 lastDev;
    /* 0x660 */ u32 tick[5]; // [4] is OSGetTick() at the last sample, [3] the one before; a read shifts [3] down through [2..0]
    /* 0x674 */ u8 readCount[2]; // samples taken by the last two reads
    /* 0x676 */ u8 mplsCmd;
    /* 0x677 */ u8 mplsCmdIssued;
    /* 0x678 */ u8 mplsMode;
    /* 0x679 */ u8 mplsModeInit;
    /* 0x67A */ u8 mplsIssued;
    /* 0x67B */ u8 mplsPostCallbackDone;
    /* 0x67C */ u8 mplsPreCallbackDone;
    /* 0x67D */ u8 mplsCheck;
    /* 0x67E */ u8 accScaleReq;
    /* 0x67F */ u8 _67F;
    /* 0x680 */ KPADControlMplsCallback mpls_ctrl_callback;
    /* 0x684 */ u32 _684;
} KPADInsideStatus;

extern KPADInsideStatus inside_kpads[WPAD_MAX_CONTROLLERS];

s32 WBCRead(WPADBLStatus* status, f64* weight, u32 size);
s32 WBCSetZEROPoint(f64 press[], u32 size);
s32 WBCGetBatteryLevel(u8 battery);
s32 WBCGetTGCWeight(f64 weight, f64* tgcWeight, WPADBLStatus* status);
s32 WBCSetupCalibration(void);
s32 WBCGetCalibrationStatus(void);
s32 WPADControlBLC(s32 chan, u8 command, WPADCallback callback);
u8 WPADiGetMplsStatus(s32 chan);
s32 WPADiControlMpls(s32 chan, u8 mode, WPADCallback callback);

BOOL KMPLSIsInit(void);
void KMPLSShutdown(void);
void KMPLSSetKpadRingBuffer(s32 chan, KPADUnifiedWpadStatus* ringBuf, KPADUnifiedWpadStatus* ringBufEx, u32 ringBufExLen);
void KMPLSSetSamplingCallback(KPADMplsSamplingCallback callback);
void KMPLSRead(s32 chan, KPADMPStatus* mpStatus, s32 idx, s32 count, KPADStatus* raw, f64 dt);
void KMPLSGetZeroDriftParam(s32 chan, f32* radius, s32* count, f32* power);

extern KPADMPDir e_dir;

s32 __KMPLS_f2i(f32 x);
f32 __KMPLS_normalize_Fxyz(Vec* v);
void __KMPLS_normalize_directionXYZ(KPADMPDir* dir, f32 limit);
void __KMPLS_make_vec_dir(KPADMPDir* dir, Vec* v1, Vec* v2);
void __KMPLS_mult_dir(KPADMPDir* a, KPADMPDir* b, KPADMPDir* dst);
void __KMPLS_linear_Fxyz(Vec* a, Vec* b, f32 t, Vec* dst);
void __KMPLS_linear_Direction(KPADMPDir* a, KPADMPDir* b, f32 t, KPADMPDir* dst);

void KPADSetBtnRepeat(s32 chan, f32 delay_sec, f32 pulse_sec);
void KPADSetPosParam(s32 chan, f32 play_radius, f32 sensitivity);
void KPADSetHoriParam(s32 chan, f32 play_radius, f32 sensitivity);
void KPADSetDistParam(s32 chan, f32 play_radius, f32 sensitivity);
void KPADSetAccParam(s32 chan, f32 play_radius, f32 sensitivity);
void KPADGetPosParam(s32 chan, f32* play_radius, f32* sensitivity);
void KPADGetHoriParam(s32 chan, f32* play_radius, f32* sensitivity);
void KPADGetDistParam(s32 chan, f32* play_radius, f32* sensitivity);
void KPADGetAccParam(s32 chan, f32* play_radius, f32* sensitivity);
void KPADEnableAimingMode(s32 chan);
void KPADDisableAimingMode(s32 chan);
u8 KPADIsEnableAimingMode(s32 chan);
void KPADSetSensorHeight(s32 chan, f32 level);
f32 KPADGetSensorHeight(s32 chan);
void KPADSetObjInterval(f32 interval);
s32 KPADRead(s32 chan, KPADStatus samplingBufs[], u32 length);
s32 KPADiRead(s32 chan, KPADStatus samplingBufs[], u32 length, s32* err, BOOL ex);
void KPADInit(void);
void KPADInitEx(KPADUnifiedWpadStatus* uniRingBufs, u32 length);
void KPADShutdown(void);
void KPADReset(void);
WPADConnectCallback KPADSetConnectCallback(s32 chan, WPADConnectCallback callback);
WPADSamplingCallback KPADSetSamplingCallback(s32 chan, WPADSamplingCallback callback);
void KPADDisableDPD(s32 chan);
void KPADEnableDPD(s32 chan);
void KPADGetUnifiedWpadStatus(s32 chan, KPADUnifiedWpadStatus* dst, u32 count);

#ifdef __cplusplus
}
#endif

#endif /* _REVOLUTION_KPAD_PRIVATE_H_ */
