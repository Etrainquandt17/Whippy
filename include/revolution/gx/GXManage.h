#ifndef REVOLUTION_GX_GXMANAGE_H
#define REVOLUTION_GX_GXMANAGE_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXDrawSyncCallback)(u16 token);
typedef void (*GXDrawDoneCallback)(void);

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback);
void GXFlush(void);
void GXPixModeSync(void);
void GXDrawDone(void);
void GXSetMisc(GXMiscToken, u32);
void GXAbortFrame(void);
void GXSetDrawSync(u16 token);
void GXSetDrawDone(void);

#ifdef __cplusplus
}
#endif

#endif
