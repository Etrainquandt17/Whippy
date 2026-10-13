#ifndef _REVOLUTION_GX_H_
#define _REVOLUTION_GX_H_

#include <tp/revolution/include/revolution/gx/GXStruct.h>
#include <tp/revolution/include/revolution/gx/GXTransform.h>
#include <tp/revolution/include/revolution/gx/GXTev.h>
#include <tp/revolution/include/revolution/gx/GXPixel.h>
#include <tp/revolution/include/revolution/gx/GXManage.h>
#include <tp/revolution/include/revolution/gx/GXFifo.h>
#include <tp/revolution/include/revolution/gx/GXCull.h>
#include <tp/revolution/include/revolution/gx/GXGeometry.h>
#include <tp/revolution/include/revolution/gx/GXVert.h>
#include <tp/revolution/include/revolution/gx/GXTexture.h>
#include <tp/revolution/include/revolution/gx/GXTev.h>
#include <tp/revolution/include/revolution/gx/GXLighting.h>
#include <tp/revolution/include/revolution/gx/GXDispList.h>
#include <tp/revolution/include/revolution/gx/GXCommandList.h>
#include <tp/revolution/include/revolution/gx/GXBump.h>
#include <tp/revolution/include/revolution/gx/GXFrameBuffer.h>
#include <tp/revolution/include/revolution/gx/GXGet.h>
#include <tp/revolution/include/revolution/gx/GXDraw.h>
#include <tp/revolution/include/revolution/gx/GXPerf.h>
#include <tp/revolution/include/revolution/gx/GXCpu2Efb.h>
#include <tp/revolution/include/revolution/gx/GXVerify.h>

// unsorted GX externs

#ifdef __cplusplus
extern "C" {
#endif

// GXMisc
void (*GXSetDrawSyncCallback(void (*cb)(u16)))(u16);
void GXSetDrawSync(u16 token);

#ifdef __cplusplus
}
#endif

#endif
