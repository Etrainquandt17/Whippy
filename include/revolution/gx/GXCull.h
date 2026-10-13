#ifndef REVOLUTION_GX_GXCULL_H
#define REVOLUTION_GX_GXCULL_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void GXSetCullMode(GXCullMode);
void GXSetCoPlanar(GXBool);

#ifdef __cplusplus
}
#endif

#endif
