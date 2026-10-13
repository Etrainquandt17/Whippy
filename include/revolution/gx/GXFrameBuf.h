#ifndef REVOLUTION_GX_GXFRAMEBUF_H
#define REVOLUTION_GX_GXFRAMEBUF_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXSetDispCopySrc(u16 left, u16 top, u16 width, u16 height);
void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height);
void GXSetDispCopyDst(u16 width, u16 height);
void GXSetTexCopyDst(u16 width, u16 height, GXTexFmt format, GXBool mipmap);
void GXSetCopyClamp(GXFBClamp clamp);
f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight);
u32 GXSetDispCopyYScale(f32 scale);
void GXSetCopyClear(GXColor color, u32 z);
void GXSetCopyFilter(GXBool antialias, const u8 samplePattern[12][2], GXBool vfilter, const u8 vfilterCoeffs[7]);
void GXSetDispCopyGamma(GXGamma gamma);
void GXCopyDisp(void* dest, GXBool clear);
void GXCopyTex(void* dest, GXBool clear);

#ifdef __cplusplus
}
#endif

#endif
