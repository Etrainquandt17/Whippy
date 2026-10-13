#ifndef REVOLUTION_MEM_H
#define REVOLUTION_MEM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMiHeapHead MEMiHeapHead;

MEMiHeapHead* MEMCreateExpHeapEx(void* start, u32 size, u16 opt);
MEMiHeapHead* MEMDestroyExpHeap(MEMiHeapHead* heap);
void* MEMAllocFromExpHeapEx(MEMiHeapHead* heap, u32 size, s32 align);
void MEMFreeToExpHeap(MEMiHeapHead* heap, void* memBlock);

#ifdef __cplusplus
}
#endif

#endif
