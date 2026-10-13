#ifndef REVOLUTION_GX_GXBUMP_H
#define REVOLUTION_GX_GXBUMP_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXSetNumIndStages(u8);
void GXSetIndTexOrder(GXIndTexStageID, GXTexCoordID, GXTexMapID);
void GXSetIndTexMtx(GXIndTexMtxID, const f32[2][3], s8);
void GXSetTevIndWarp(GXTevStageID, GXIndTexStageID, GXBool, GXBool, GXIndTexMtxID);
void GXSetTevIndirect(GXTevStageID, GXIndTexStageID, GXIndTexFormat, GXIndTexBiasSel, GXIndTexMtxID, GXIndTexWrap, GXIndTexWrap, GXBool, GXBool, GXIndTexAlphaSel);
void GXSetIndTexCoordScale(GXIndTexStageID, GXIndTexScale, GXIndTexScale);
void GXSetTevDirect(GXTevStageID);

#ifdef __cplusplus
}
#endif

#endif
