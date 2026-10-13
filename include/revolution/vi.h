#ifndef REVOLUTION_VI_H
#define REVOLUTION_VI_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void VIWaitForRetrace(void);
void VIConfigure(const struct _GXRenderModeObj* rmode);
void VIFlush(void);
void VISetBlack(int black);
u32 VIGetTvFormat(void);
u32 VIGetDTVStatus(void);
void VISetNextFrameBuffer(void* fb);

#ifdef __cplusplus
}
#endif

#endif
