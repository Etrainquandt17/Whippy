#ifndef REVOLUTION_GX_GXGEOMETRY_H
#define REVOLUTION_GX_GXGEOMETRY_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXSetVtxDesc(GXAttr, GXAttrType);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmt(GXVtxFmt, GXAttr, GXCompCnt, GXCompType, u8);
void GXSetVtxAttrFmtv(GXVtxFmt, const GXVtxAttrFmtList*);
void GXSetArray(GXAttr, const void*, u8);
void GXBegin(GXPrimitive, GXVtxFmt, u16);
void GXSetTexCoordGen2(GXTexCoordID, GXTexGenType, GXTexGenSrc, u32, GXBool, u32);
void GXSetNumTexGens(u8);
void GXInvalidateVtxCache(void);
void GXSetLineWidth(u8, GXTexOffset);
void GXSetPointSize(u8, GXTexOffset);
void GXEnableTexOffsets(GXTexCoordID, GXBool, GXBool);

static inline void GXSetTexCoordGen(GXTexCoordID coord, GXTexGenType type, GXTexGenSrc src, u32 mtx) {
    GXSetTexCoordGen2(coord, type, src, mtx, GX_FALSE, GX_PTIDENTITY);
}

#ifdef __cplusplus
}
#endif

#endif
