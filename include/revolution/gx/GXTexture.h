#ifndef REVOLUTION_GX_GXTEXTURE_H
#define REVOLUTION_GX_GXTEXTURE_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 maxLod);
void GXLoadTexObj(const GXTexObj* obj, GXTexMapID id);
void GXInitTexObj(GXTexObj* obj, void* image, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter minFilter, GXTexFilter magFilter, f32 minLod, f32 maxLod, f32 lodBias, GXBool biasClamp,
                     GXBool edgeLod, GXAnisotropy maxAniso);
u16 GXGetTexObjWidth(const GXTexObj* obj);
u16 GXGetTexObjHeight(const GXTexObj* obj);
void GXInvalidateTexAll(void);
void GXTexModeSync(void);

#ifdef __cplusplus
}
#endif

#endif
