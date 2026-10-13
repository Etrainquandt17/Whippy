#ifndef REVOLUTION_TPL_H
#define REVOLUTION_TPL_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TPLDescriptor TPLDescriptor;

typedef struct TPLPalette {
    u32 versionNumber;
    u32 numDescriptors;
    TPLDescriptor* descriptorArray;
} TPLPalette;

void TPLBind(TPLPalette* palette);
void TPLGetGXTexObjFromPalette(TPLPalette* palette, GXTexObj* texObj, u32 index);

#ifdef __cplusplus
}
#endif

#endif
