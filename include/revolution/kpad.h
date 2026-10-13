#ifndef REVOLUTION_KPAD_H
#define REVOLUTION_KPAD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*WPADAlloc)(u32 size);
typedef int (*WPADFree)(void* ptr);

void WPADRegisterAllocator(WPADAlloc alloc, WPADFree free);

void KPADInit(void);
void KPADReset(void);
void KPADShutdown(void);
void KPADSetPosParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADSetBtnRepeat(s32 chan, f32 delaySec, f32 pulseSec);
void KPADSetAccParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADSetDistParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADEnableAimingMode(s32 chan);

int PADInit(void);

void OSSleepTicks(s64 ticks);

#ifdef __cplusplus
}
#endif

#endif
