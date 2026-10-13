#ifndef REVOLUTION_GX_GXLIGHTING_H
#define REVOLUTION_GX_GXLIGHTING_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXInitLightAttn(GXLightObj*, f32, f32, f32, f32, f32, f32);
void GXInitLightPos(GXLightObj*, f32, f32, f32);
void GXInitLightColor(GXLightObj*, GXColor);
void GXLoadLightObjImm(const GXLightObj*, GXLightID);
void GXInitLightDistAttn(GXLightObj*, f32, f32, GXDistAttnFn);
void GXInitLightDir(GXLightObj*, f32, f32, f32);
void GXInitLightSpot(GXLightObj*, f32, GXSpotFn);
void GXSetNumChans(u8);
void GXInitSpecularDir(GXLightObj*, f32, f32, f32);
void GXInitSpecularDirHA(GXLightObj*, f32, f32, f32, f32, f32, f32);
void GXSetChanAmbColor(GXChannelID, GXColor);
void GXSetChanMatColor(GXChannelID, GXColor);
void GXSetChanCtrl(GXChannelID, GXBool, GXColorSrc, GXColorSrc, u32, GXDiffuseFn, GXAttnFn);

#ifdef __cplusplus
}
#endif

#endif
